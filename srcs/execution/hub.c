/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:53:52 by panger            #+#    #+#             */
/*   Updated: 2024/01/17 12:35:50 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execution_hub(t_token *tokens, char ***env)
{
	t_block	*blocks;

	if (expand(tokens, *env) == -1)
		return (-1);
	blocks = words_to_blocks(tokens);
	if (!blocks)
		return (-1);
	lst_free(tokens);
	command_receiver(blocks, env);
	free_blocks(blocks);
	return (0);
}
