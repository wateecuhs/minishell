/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 18:55:11 by waticouz          #+#    #+#             */
/*   Updated: 2024/01/18 17:33:21 by panger           ###   ########.fr       */
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
			tmp->value = expand_word(tmp, tmp->value, env);
			if (tmp->value == NULL)
				return (-1);
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (0);
}
