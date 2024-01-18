/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:53:52 by panger            #+#    #+#             */
/*   Updated: 2024/01/18 14:02:43 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execution_hub(t_token *tokens, char ***env)
{
	t_block	*blocks;

	if (expand(tokens, *env) == -1)
		return (-1);
	blocks = words_to_blocks(tokens, *env);
	if (!blocks)
		return (-1);
	lst_free(tokens);
	if (command_receiver(blocks, env) == -1)
		return (free_blocks(blocks), -1);
	free_blocks(blocks);
	return (0);
}
