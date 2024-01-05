/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:45:19 by panger            #+#    #+#             */
/*   Updated: 2024/01/05 17:01:26 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_in_fd(t_token *start)
{
	int	fd;

	fd = -1;
	while (start->prev && start->prev->type != PIPE)
		start = start->prev;
	while (start->next && start->next->type != PIPE)
	{
		
		start = start->next;
	}
}

int	get_fd(int fd[4], t_token *input, int i, char *cmd)
{
	int	count;

	count = 0;
	while (input && ft_strcmp(input->value, cmd) != 0)
		input = input->next;
	if (!input)
		return (-1);
	fd[2 + IN] = get_in_fd(input);
	fd[2 + OUT] = get_out_fd(input);
}