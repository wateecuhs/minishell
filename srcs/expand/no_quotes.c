/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:14:56 by panger            #+#    #+#             */
/*   Updated: 2024/01/22 15:40:26 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

int	make_next(t_token *token, char *value)
{
	t_token	*tmp;
	char	*value_dup;

	value_dup = ft_strdup(value);
	if (!value_dup)
		return (-1);
	tmp = lst_new(WORD, value_dup);
	if (!tmp)
		return (free(value_dup), -1);
	tmp->next = token->next;
	tmp->ignore = 1;
	token->next = tmp;
	token = token->next;
	return (0);
}

int	loop_join(t_token *token, char *content, char **ret, char *endofstr)
{
	size_t	i;
	char	**tab;

	i = 0;
	if (!content)
	{
		*ret = ft_strjoin_free(*ret, endofstr);
		return (0);
	}
	tab = ft_split(content, ' ');
	if (!tab)
		return (1);
	if (content[0] != ' ' && content[0] != '\0')
	{
		*ret = ft_strjoin_free(*ret, tab[i++]);
		if (has_spaces(content) == 0)
			*ret = ft_strjoin_free(*ret, endofstr);
	}
	while (tab[i])
	{
		if (make_next(token, tab[i++]) == -1)
			return (freetab(tab), 1);
	}
	freetab(tab);
	return (0);
}

char	*expand_var_noquotes(t_token *token, size_t *start,
			size_t stop, char *content)
{
	char	*ret;

	ret = ft_strndup(token->value, *start);
	if (!ret)
		return (free(token->value), free(content), NULL);
	*start = ft_strlen(ret) + ft_strlen(content) - 1;
	if (loop_join(token, content, &ret, &(token->value)[stop + 1]) == 1)
		return (free(token->value), free(content), NULL);
	free(token->value);
	return (ret);
}

int	expand_word_var(t_token *token, char **src, size_t *i, char **env)
{
	int		env_var;
	char	*tmp;
	char	*s;

	s = *src;
	env_var = get_var_name(s, *i);
	if (env_var != -1)
	{
		tmp = ft_strndup(&s[*i + 1], env_var - *i);
		if (!tmp)
			return (-1);
		tmp = parse_env(env, tmp);
		s = expand_var_noquotes(token, i, env_var, tmp);
		if (tmp)
			free(tmp);
		if (!s)
			return (-1);
	}
	*src = s;
	token->value = s;
	return (0);
}
