/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:29:27 by panger            #+#    #+#             */
/*   Updated: 2024/01/16 13:23:43 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_exec(t_block *block, int fd[4], char ***env, t_block *head)
{
	char	*path;
	int		exit_code;

	exit_code = 0;
	check_fds(fd, head, env);
	if (is_cmd_builtin(block->cmd) == 0)
	{
		exit_code = exec_builtin(block, env, fd, head);
		free_and_exit(head, *env, exit_code);
	}
	if (dup_job(&fd[2]) == -1)
		free_and_exit(head, *env, 1);
	if (!(block->cmd))
		free_and_exit(head, *env, 0);
	path = find_path(block->cmd, *env);
	if (!path)
	{
		if (errno == 13)
			free_and_exit(head, *env, 126);
		free_and_exit(head, *env, 127);
	}
	remove_empty(env);
	execve(path, block->args, *env);
	perror_prefix(block->cmd);
	free_and_exit(head, *env, 126);
}

void	parent_process(int *fds, int *p)
{
	if (fds[IN] != 0)
		close(fds[IN]);
	if (fds[OUT] != 1)
		close(fds[OUT]);
	fds[IN] = p[READ];
}

int	wait_pids(t_block *blocks, int code)
{
	while (blocks)
	{
		if (blocks->pid != -1)
			waitpid(blocks->pid, &g_status_code, 0);
		blocks = blocks->next;
	}
	if (WIFEXITED(g_status_code))
		g_status_code = WEXITSTATUS(g_status_code);
	if (code >= 0)
		g_status_code = code;
	return (g_status_code);
}

int	fork_exec(t_block *block, int fds[4], char ***env, t_block *head)
{
	int	pid;

	if (is_cmd_builtin(block->cmd) == 0 && head == block && block->next == NULL)
	{
		if (fds[2 + IN] == -1 || fds[2 + OUT] == -1)
		{
			g_status_code = 1;
			return (-1);
		}
		g_status_code = exec_builtin(block, env, fds, head);
		return (-1);
	}
	pid = fork();
	if (pid == -1)
		error_msg(NULL);
	if (pid == 0)
	{
		close(fds[READ]);
		command_exec(block, fds, env, head);
	}
	return (pid);
}

int	command_receiver(t_block *blocks, char ***env)
{
	t_block	*head;
	int		fds[4];
	int		i;
	int		code;

	i = 0;
	code = -1;
	head = blocks;
	while (blocks)
	{
		if (pipe(fds) == -1)
			error_msg(NULL);
		get_fd(fds, blocks, i);
		if (!(blocks->cmd) || code == -1)
			blocks->pid = fork_exec(blocks, fds, env, head);
		parent_process(&fds[2], fds);
		blocks = blocks->next;
		i++;
	}
	close(fds[IN]);
	close(fds[OUT]);
	i = wait_pids(head, code);
	return (i);
}
