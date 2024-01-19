/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 18:55:11 by waticouz          #+#    #+#             */
/*   Updated: 2024/01/19 18:52:33 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_word(t_token *token, char *s, char **env)
{
	size_t	i;
	int		val;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && i < ft_strlen(s))
	{
		if (s[i] == '\'')
			expand_single_quotes(&s, &i);
		else if (s[i] == '"')
		{
			val = expand_double_quotes(&s, &i, env);
			if (val == -1)
				return (free(s), NULL);
			i = val - 1;
		}
		else if (s[i] == '$')
		{
			if (expand_word_var(token, &s, &i, env) == -1)
				return (free(s), NULL);
		}
		i++;
	}
	return (s);
}

void	empty_cmd(t_token *head, t_token *token)
{
	t_token	*tmp;

	tmp = head;
	while (tmp && tmp != token)
		tmp = tmp->next;
	if (!tmp)
		return ;
	tmp = tmp->prev;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
			return ;
		tmp = tmp->prev;
	}
	if (ft_strcmp(token->value, "\"\"") == 0
		|| ft_strcmp(token->value, "''") == 0)
		token->ignore = 1;
}

int	expand(t_token *head, char **env)
{
	t_token	*tmp;

	if (!head)
		return (-1);
	tmp = head;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			tmp->next->value = expand_limiter(tmp->next->value);
			if (tmp->next->value == NULL)
				return (-1);
			tmp = tmp->next;
		}
		else if (tmp->type == WORD && tmp->ignore == 0)
		{
			empty_cmd(head, tmp);
			tmp->value = expand_word(tmp, tmp->value, env);
			if (tmp->value == NULL)
				return (-1);
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (0);
}
