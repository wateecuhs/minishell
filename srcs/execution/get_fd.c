/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:45:19 by panger            #+#    #+#             */
/*   Updated: 2024/01/12 10:45:38 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*set_fd_to_use(int *fd, int fd_in, int fd_out)
{
	fd[3] = fd_in;
	fd[2] = fd_out;
	return (fd);
}

int	get_out(int *fd, t_redirs *redirs)
{
	if (redirs->type == REDIRECT_OUT || redirs->type == REDIRECT_APPEND)
	{
			if (*fd != 1)
				close(*fd);
		if (redirs->type == REDIRECT_OUT)
			*fd =  open(redirs->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (redirs->type == REDIRECT_APPEND)
			*fd = open(redirs->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (*fd == -1)
			return (perror(redirs->value), -1);
	}
	return (0);
}

int	get_in(int *fd, t_redirs *redirs)
{
	if (redirs->type == REDIRECT_IN)
	{
		if (*fd != 0)
			close(*fd);
		*fd = open(redirs->value, O_RDONLY);
		if (*fd == -1)
			return (perror(redirs->value), -1);
	}
	if (redirs->type == HEREDOC)
	{
		if (*fd != 0)
			close(*fd);
		*fd = redirs->heredoc_fd;		
	}
	return (0);
}

void	get_fd(int fd[4], t_block *block, int i)
{
	int	in;
	int	out;

	in = fd[2 + IN];
	if (i == 0)
		in = 0;
	out	= fd[WRITE];
	if (block->next == NULL)
		out = 1;
	while (block->redirs)
	{
		if (block->redirs->type == REDIRECT_IN || block->redirs->type == HEREDOC)
			get_in(&in, block->redirs);
		if (block->redirs->type == REDIRECT_OUT || block->redirs->type == REDIRECT_APPEND)
			get_out(&out, block->redirs);
		block->redirs = block->redirs->next;
		if (in == -1 || out == -1)
			break;
	}
	fd[2 + IN] = in;
	fd[2 + OUT] = out;
}
