/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:45:19 by panger            #+#    #+#             */
/*   Updated: 2024/01/05 18:27:52 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_fd_block(int fd[2], t_token *start)
{
	t_token *last_in;
	t_token *last_out;
	
	fd[0] = -1;
	fd[1] = -1;
	last_in = NULL;
	last_out = NULL;
	while (start->prev && start->prev->type != PIPE)
		start = start->prev;
	while (start->next && start->next->type != PIPE)
	{
		if (start->type == REDIRECT_IN)
			last_in = start->next;
		if (start->type == REDIRECT_OUT || start->type == REDIRECT_APPEND)
			last_out = start->next;
		start = start->next;
	}
	fd[IN] = open_file(last_in);
	fd[OUT] = open_file(last_out);
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