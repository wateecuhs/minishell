/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waticouz <waticouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 15:45:01 by waticouz          #+#    #+#             */
/*   Updated: 2024/01/01 16:02:30 by waticouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_fd_in(t_token *head, t_token *target)
{
	int	fd;

	fd = 1;
	while (head && head != target)
	{
		if (head->value == HEREDOC)
		{
			
		}
		head = head->next;
	}
}