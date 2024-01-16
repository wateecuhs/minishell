/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:23:52 by panger            #+#    #+#             */
/*   Updated: 2024/01/16 13:13:16 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_block	*get_block(t_token *token)
{
	t_block	*ret;

	ret = (t_block *)malloc(sizeof(t_block));
	if (!ret)
		return (NULL);
	ret->next = NULL;
	ret->cmd = get_cmd(token);
	ret->args = get_args(token);
	ret->redirs = get_redirs(token);
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

t_block	*words_to_blocks(t_token *tokens)
{
	t_token	*lst;
	t_block	*blocks;

	blocks = NULL;
	lst = tokens;
	while (lst)
	{
		lst_addback_blocks(&blocks, get_block(lst));
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
		if (node->type == WORD && ft_strcmp(node->value, "") != 0)
			i++;
		if (node->type == REDIRECT_IN || node->type == REDIRECT_OUT
			|| node->type == REDIRECT_APPEND || node->type == HEREDOC)
			node = node->next;
		node = node->next;
	}
	return (i);
}
