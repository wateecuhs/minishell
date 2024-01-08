/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:45:19 by panger            #+#    #+#             */
/*   Updated: 2024/01/08 16:18:59 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_out_fd(int fd, t_token *start)
{
	fd = 0;
	while (start->prev && start->prev->type != PIPE)
		start = start->prev;
	while (start->next && start->next->type != PIPE)
	{
		if (start->type == REDIRECT_IN)
		{
			start = start->next;
			if (fd != 0)
				close(fd);
			fd = open(start->value, O_RDONLY);
			if (fd == -1)
				return (perror(start->type), -1);
		}
		start = start->next;
	}
	return (fd);
}

int	get_in_fd(int fd, t_token *start)
{
	fd = 0;
	while (start->prev && start->prev->type != PIPE)
		start = start->prev;
	while (start->next && start->next->type != PIPE)
	{
		if (start->type == REDIRECT_IN)
		{
			start = start->next;
			if (fd != 0)
				close(fd);
			fd = open(start->value, O_RDONLY);
			if (fd == -1)
				return (perror(start->type), -1);
		}
		start = start->next;
	}
	return (fd);
}

int	get_fd(int fd[4], t_token *input, int i, char *cmd)
{
	int	count;

	count = 0;
	while (input && ft_strcmp(input->value, cmd) != 0)
		input = input->next;
	if (!input)
		return (-1);
	get_fd_block(&fd[2], input);
}