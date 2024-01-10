/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:29:27 by panger            #+#    #+#             */
/*   Updated: 2024/01/10 18:15:07 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_job(int fd[2])
{
	if (fd[IN] == -1 || fd[OUT] == -1)
		exit(EXIT_FAILURE);
	if (fd[IN] != 0)
	{
		if (dup2(fd[IN], STDIN_FILENO) == -1)
			error_msg(NULL);
		close(fd[IN]);
	}
	if (fd[OUT] != 1)
	{
		if (dup2(fd[OUT], STDOUT_FILENO) == -1)
			error_msg(NULL);
		close(fd[OUT]);
	}
}

void	command_exec(t_block *block, int fd[2], char **env)
{
	char	*path;

	dup_job(fd);
	path = find_path(block->cmd, env);
	if (!path)
	{
		dup2(2, 1);
		close(2);
		if (access(block->cmd, F_OK) == -1)
			printf("minishell: %s: command not found\n", block->cmd);
		else if (access(block->cmd, F_OK) != -1  && access(block->cmd, X_OK) == -1)
			printf("minishell: %s: permission denied\n", block->cmd);
		exit(127);
	}
	execve(path, block->args, env);
	dup2(2, 1);
	close(2);
	printf("minishell: %s: failed to execute a command\n", block->cmd);
	exit(126);
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
		waitpid(blocks->pid, &g_status_code, 0);
		blocks = blocks->next;
	}
	g_status_code = WEXITSTATUS(g_status_code);	
	if (code != -1)
		g_status_code = code;
	return (g_status_code);
}

int	fork_exec(t_block *block, int *fds, char **env)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		error_msg(NULL);
	if (pid == 0)
	{
		close(fds[READ]);
		command_exec(block, &fds[2], env);
	}
	return (pid);
}

int	command_receiver(t_block *blocks, char **env)
{
	t_block *head;
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
		if (is_builtin(blocks, &env, &code) == -1)
			blocks->pid = fork_exec(blocks, fds, env);
		parent_process(&fds[2], fds);
		blocks = blocks->next;
		i++;
	}
	i = wait_pids(head, code);
	return (i);
}
