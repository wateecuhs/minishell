/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:36:16 by panger            #+#    #+#             */
/*   Updated: 2024/01/18 17:04:03 by panger           ###   ########.fr       */
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
	free_redir(blocks->redirs);
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
		free_redir(blocks->redirs);
		tmp1 = blocks->next;
		free(blocks);
		blocks = tmp1;
	}
}

void	free_redir(t_redirs *redirs)
{
	t_redirs	*tmp;

	while (redirs)
	{
		if (redirs->value)
			free(redirs->value);
		tmp = redirs->next;
		free(redirs);
		redirs = tmp;
	}
}