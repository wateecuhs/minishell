/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:36:16 by panger            #+#    #+#             */
/*   Updated: 2024/01/12 12:37:13 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_and_exit(t_block *blocks, char **env, int exitcode)
{
	free_blocks(blocks);
	free_env(env);
	exit(exitcode);
}
void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void	free_single_block(t_block *blocks)
{
	int			i;
	t_redirs	*tmp2;

	if (blocks->cmd)
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
	free(blocks);
}

void	free_blocks(t_block *blocks)
{
	int			i;
	t_block		*tmp1;
	t_redirs	*tmp2;

	while (blocks)
	{
		if (blocks->cmd)
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
