/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waticouz <waticouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:29:27 by panger            #+#    #+#             */
/*   Updated: 2023/12/29 16:07:54 by waticouz         ###   ########.fr       */
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

int	command_receiver(int nb_cmd, char **cmds, char **env, int *fd_in_and_out)
{
	int	fds[4];
	int	*pid;
	int	i;

	i = -1;
	pid = (int *)malloc(sizeof(int) * nb_cmd);
	if (!pid)
		error_msg("malloc");
	while (++i < nb_cmd)
	{
		if (pipe(fds) == -1)
			error_msg(NULL);
		if (i == 0)
			set_fd_to_use(fds, fd_in_and_out[IN], fds[WRITE]);
		else if (i == nb_cmd - 1)
			set_fd_to_use(fds, fds[2 + IN], fd_in_and_out[OUT]);
		else
			set_fd_to_use(fds, fds[2 + IN], fds[2 + OUT]);
		pid[i] = fork_exec(cmds[i], fds, env, pid);
		parent_process(&fds[2], fds);
	}
	i = wait_pids(pid, nb_cmd);
	return (i);
}
