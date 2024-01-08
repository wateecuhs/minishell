/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:53:52 by panger            #+#    #+#             */
/*   Updated: 2024/01/08 18:25:36 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execution_hub(t_token *tokens, char **env)
{
	t_block	*blocks;

	if (expand(tokens, env) == -1)
		return (-1);
	blocks = words_to_blocks(tokens);
	while (blocks)
	{
		printf("in block %s\n", blocks->cmd);
		blocks = blocks->next;
	}
	/* if (execute(tokens, env) == -1)
		return (-1); */
}