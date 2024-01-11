/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:36:16 by panger            #+#    #+#             */
/*   Updated: 2024/01/11 19:39:29 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_blocks(t_block *blocks)
{
	int			i;
	t_block		*tmp1;
	t_redirs	*tmp2;

	while (blocks)
	{
		free(blocks->cmd);
		i = 0;
		while (blocks->args[i])
			free(blocks->args[i++]);
		free(blocks->args);
		while (blocks->redirs)
		{
			free(blocks->redirs->value);
			tmp2 = blocks->redirs->next;
			free(blocks->redirs);
			blocks->redirs = tmp2;
		}
		tmp1 = blocks->next;
		free(blocks);
		blocks = tmp1;
	}
}
