/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:23:52 by panger            #+#    #+#             */
/*   Updated: 2024/01/22 15:08:44 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_block	*get_block(t_token *token, char **env)
{
	t_block	*ret;

	ret = (t_block *)malloc(sizeof(t_block));
	if (!ret)
		return (perror_prefix("malloc"), NULL);
	ret->next = NULL;
	if (get_cmd(token, &(ret->cmd)) == -1)
		return (free(ret), NULL);
	ret->args = get_args(token);
	if (!ret->args)
		return (free(ret->cmd), free(ret), NULL);
	if (get_redirs(token, env, &(ret->redirs)) == -1)
		return (free(ret->cmd), free_env(ret->args), free(ret), NULL);
	if (check_hd(ret->redirs) == 0)
	{
		free_single_block(ret);
		return (NULL);
	}
	ret->pid = -1;
	return (ret);
}

t_token	*next_block(t_token *tokens)
{
	while (tokens && tokens->type != PIPE)
		tokens = tokens->next;
	if (tokens)
		tokens = tokens->next;
	return (tokens);
}

t_block	*words_to_blocks(t_token *tokens, char **env)
{
	t_token	*lst;
	t_block	*blocks;
	t_block	*tmp;

	blocks = NULL;
	lst = tokens;
	while (lst)
	{
		tmp = get_block(lst, env);
		if (!tmp)
		{
			free_blocks(blocks);
			return (NULL);
		}
		lst_addback_blocks(&blocks, tmp);
		lst = next_block(lst);
	}
	return (blocks);
}

int	count_blocks(t_token *tokens)
{
	int		i;
	t_token	*node;

	i = 1;
	node = tokens;
	while (node)
	{
		if (node->type == PIPE)
			i++;
		node = node->next;
	}
	return (i);
}

int	count_words_in_block(t_token *tokens)
{
	int		i;
	t_token	*node;

	i = 0;
	node = tokens;
	while (node && node->type != PIPE)
	{
		if (node->type == WORD)
			i++;
		if (node->type == REDIRECT_IN || node->type == REDIRECT_OUT
			|| node->type == REDIRECT_APPEND || node->type == HEREDOC)
			node = node->next;
		node = node->next;
	}
	return (i);
}
