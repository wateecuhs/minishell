/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_addback_blocks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcindrak <dcindrak@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:12:38 by panger            #+#    #+#             */
/*   Updated: 2024/01/18 15:48:54 by dcindrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_addback_blocks(t_block **lst, t_block *new)
{
	t_block	*temp;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

int	lst_addback_redirs(t_redirs **lst, t_redirs *new)
{
	t_redirs	*temp;

	if (!new)
		return (1);
	if (!(*lst))
	{
		*lst = new;
		return (0);
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	return (0);
}
