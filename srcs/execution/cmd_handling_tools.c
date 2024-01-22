/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handling_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:21:33 by panger            #+#    #+#             */
/*   Updated: 2024/01/22 11:17:09 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_fds(int fd[4], t_block *head, char ***env)
{
	if (fd[2 + IN] == -1 || fd[2 + OUT] == -1)
		free_and_exit(head, *env, 1);
}

int	is_hd(t_redirs *redirs)
{
	int	redir;

	redir = 0;
	while (redirs)
	{
		if (redirs->type == HEREDOC)
			redir = 1;
		if (redirs->type == REDIRECT_IN)
			redir = 0;
		redirs = redirs->next;
	}
	return (redir);
}

t_redirs	*last_hd(t_redirs *redirs)
{
	t_redirs	*tmp;

	tmp = NULL;
	while (redirs)
	{
		if (redirs->type == HEREDOC)
			tmp = redirs;
		if (redirs->type == REDIRECT_IN)
			tmp = NULL;
		redirs = redirs->next;
	}
	return (tmp);
}

int	handle_hd(t_redirs *hd, t_block *head, char **env)
{
	int	i;
	int	len;
	int	p[2];
	int	pid;

	if (pipe(p) == -1)
		return (perror_prefix("pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (perror_prefix("fork"), -1);
	if (pid == 0)
	{
		i = 0;
		close(p[READ]);
		len = ft_strlen(hd->value);
		while (i < len)
		{
			if ((len - i) / 512 == 0)
				write(p[WRITE], &(hd->value)[i], (len - i) % 512);
			else
				write(p[WRITE], &(hd->value)[i], 512);
			i += 512;
		}
		close(p[WRITE]);
		free_and_exit(head, env, 0);
	}
	close(p[WRITE]);
	if (dup2(p[READ], STDIN_FILENO) == -1)
			return (perror_prefix("Broken pipe"), -1);
	close(p[READ]);
	return (0);
}

int	dup_job(t_redirs *redirs, int fd[2], t_block *head, char **env)
{
	t_redirs	*tmp;

	if (is_hd(redirs) == 1)
	{
		tmp = last_hd(redirs);
		handle_hd(tmp, head, env);
	}
	else if (fd[IN] != 0)
	{ 
		if (dup2(fd[IN], STDIN_FILENO) == -1)
			return (perror_prefix("Broken pipe"), -1);
		close(fd[IN]);
	}
	if (fd[OUT] != 1)
	{
		if (dup2(fd[OUT], STDOUT_FILENO) == -1)
			return (perror_prefix("Broken pipe"), -1);
		close(fd[OUT]);
	}
	return (0);
}

void	remove_empty(char ***env)
{
	int	i;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strchr((*env)[i], '=') == -1)
			(*env)[i] = NULL;
		i++;
	}
}
