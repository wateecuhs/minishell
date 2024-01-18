/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:57:42 by panger            #+#    #+#             */
/*   Updated: 2024/01/18 12:36:30 by panger           ###   ########.fr       */
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

char	*get_cmd(t_token *token)
{
	t_token	*node;
	char	*tmp;

	node = token;
	while (node && node->type != PIPE)
	{
		if (node->type == WORD && ft_strcmp(node->value, "") != 0)
		{
			tmp = ft_strdup(node->value);
			if (!tmp)
				return (perror("malloc"), NULL);
			return (tmp);
		}
		if (node->type == REDIRECT_IN || node->type == REDIRECT_OUT
			|| node->type == REDIRECT_APPEND || node->type == HEREDOC)
			node = node->next;
		node = node->next;
	}
	return (NULL);
}

char	**get_args(t_token *token)
{
	char	**ret;
	t_token	*node;
	int		i;

	i = 0;
	ret = (char **)malloc(sizeof(char *) * (count_words_in_block(token) + 1));
	if (!ret)
		return (NULL);
	node = token;
	while (node && node->type != PIPE)
	{
		if (node->type == WORD && ft_strcmp(node->value, "") != 0)
		{
			ret[i++] = ft_strdup(node->value);
			if (!(ret[i - 1]))
				return (NULL);
		}
		if (node->type == REDIRECT_IN || node->type == REDIRECT_OUT
			|| node->type == REDIRECT_APPEND || node->type == HEREDOC)
			node = node->next;
		node = node->next;
	}
	ret[i] = NULL;
	return (ret);
}

t_redirs	*assign_redir(t_token *token, char **env)
{
	t_redirs	*ret;

	ret = (t_redirs *)malloc(sizeof(t_redirs));
	if (!ret)
		return (NULL);
	ret->next = NULL;
	ret->type = token->type;
	ret->value = ft_strdup(token->next->value);
	if (!(ret->value))
		return (free(ret), NULL);
	if (ret->type == HEREDOC)
		ret->heredoc_fd = get_heredoc(token->next->value, env);
	else
		ret->heredoc_fd = -1;
	return (ret);
}

t_redirs	*get_redirs(t_token *token, char **env)
{
	t_token		*node;
	t_redirs	*ret;

	node = token;
	ret = NULL;
	while (node && node->type != PIPE)
	{
		if (node->type == REDIRECT_IN || node->type == REDIRECT_OUT
			|| node->type == REDIRECT_APPEND || node->type == HEREDOC)
		{
			lst_addback_redirs(&ret, assign_redir(node, env));
			node = node->next;
		}
		node = node->next;
	}
	return (ret);
}
