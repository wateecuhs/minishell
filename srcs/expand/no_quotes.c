/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:14:56 by panger            #+#    #+#             */
/*   Updated: 2024/01/15 12:30:37 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	loop_join(char *content, char *s, char **ret)
{
	size_t	i;
	char	**tab;

	i = 0;
	tab = ft_split(content, ' ');
	if (!tab)
		return (1);
	while (tab[i])
	{
		*ret = ft_strjoin_free(*ret, tab[i]);
		if (!*ret)
			return (free(s), freetab(tab), 1);
		if (tab[i + 1] != NULL)
			*ret = ft_strjoin_free(*ret, " ");
		if (!*ret)
			return (free(s), freetab(tab), 1);
		i++;
	}
	freetab(tab);
	return (0);
}

char	*expand_var_noquotes(char *s, size_t *start, size_t stop, char *content)
{
	char	*ret;
	int		do_free;

	do_free = 0;
	if (!content)
	{
		content = ft_strdup("");
		do_free = 1;
	}
	if (!content)
		return (free(s), NULL);
	ret = ft_strndup(s, *start);
	if (!ret)
		return (free(s), free(content), NULL);
	if (loop_join(content, s, &ret) == 1)
		return (free(s), free(content), NULL);
	*start = ft_strlen(ret) - 1;
	ret = ft_strjoin_free(ret, &s[stop + 1]);
	if (!ret)
		return (free(s), free(content), NULL);
	free(s);
	if (do_free)
		free(content);
	return (ret);
}

int	expand_word_var(char **src, size_t *i, char **env)
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
		s = expand_var_noquotes(s, i, env_var, tmp);
		if (!s)
			return (free(tmp), -1);
		if (tmp)
			free(tmp);
	}
	*src = s;
	return (0);
}
