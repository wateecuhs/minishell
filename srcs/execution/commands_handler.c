/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:29:27 by panger            #+#    #+#             */
/*   Updated: 2024/01/05 16:52:15 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_exec(char *cmd, int fd[2], char **env)
{
	char	**args;
	char	*path;

	if (fd[IN] == -1 || fd[OUT] == -1)
		exit(EXIT_FAILURE);
	if (dup2(fd[IN], STDIN_FILENO) == -1)
		error_msg(NULL);
	close(fd[IN]);
	if (dup2(fd[OUT], STDOUT_FILENO) == -1)
		error_msg(NULL);
	close(fd[OUT]);
	args = ft_split(cmd, " \t\v\n\f\r");
	if (!args)
		error_msg(NULL);
	path = find_path(cmd, env);
	if (!path)
	{
		freetab(args);
		ft_printf("pipex: command not found: %s\n", cmd);
		exit(EXIT_FAILURE);
	}
	execve(path, args, env);
	ft_printf("pipex: failed to execute a command: %s\n", cmd);
	exit(EXIT_FAILURE);
}

void	parent_process(int *fd_to_use, int *p)
{
	close(fd_to_use[IN]);
	close(fd_to_use[OUT]);
	fd_to_use[IN] = p[READ];
}

int	wait_pids(int *pid, int len)
{
	int	i;
	int	status;

	i = 0;
	while (i < len)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	free(pid);
	return (status);
}

int	fork_exec(char *cmd, int *fds, char **env, int *pid_tab)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		error_msg(NULL);
	if (pid == 0)
	{
		free(pid_tab);
		close(fds[READ]);
		command_exec(cmd, &fds[2], env);
	}
	return (pid);
}

//need to null terminate cmds
int	command_receiver(char **cmds, char **env, int *fd_in_and_out, t_token *input)
{
	int	fds[4];
	int	*pid;
	int	i;

	i = 0;
	pid = (int *)malloc(sizeof(int) * ft_tablen(cmds));
	if (!pid)
		error_msg("malloc");
	while (cmds[i])
	{
		if (pipe(fds) == -1)
			error_msg(NULL);
		get_fds(fds, input, i);
		set_fd_to_use(fds, fds[2 + IN], fds[2 + OUT]);
		pid[i] = fork_exec(cmds[i], fds, env, pid);
		parent_process(&fds[2], fds);
	}
	i = wait_pids(pid, ft_tablen(cmds));
	return (i);
}
