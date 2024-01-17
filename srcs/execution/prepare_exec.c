/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:23:52 by panger            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/01/17 15:44:13 by panger           ###   ########.fr       */
=======
/*   Updated: 2024/01/17 12:34:22 by panger           ###   ########.fr       */
>>>>>>> 603c0bf6f9f746acf9765b0d265f1eb062b1a72e
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_hd(t_redirs *redir)
{
	t_redirs	*tmp;

	tmp = redir;
	while (tmp)
	{
		if (tmp->type == HEREDOC && tmp->heredoc_fd == -1)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

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
<<<<<<< HEAD
	if (check_hd(ret->redirs) == 0)
=======
	if (!ret->redirs)
>>>>>>> 603c0bf6f9f746acf9765b0d265f1eb062b1a72e
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

t_block	*words_to_blocks(t_token *tokens)
{
	t_token	*lst;
	t_block	*blocks;
	t_block	*tmp;

	blocks = NULL;
	lst = tokens;
	while (lst)
	{
		tmp = get_block(lst);
		if (!tmp)
		{
			free_blocks(blocks);
			return (NULL);
		}
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
