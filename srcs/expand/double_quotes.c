/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waticouz <waticouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 15:07:33 by waticouz          #+#    #+#             */
/*   Updated: 2023/12/29 15:59:59 by waticouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_env(char **env, char *to_find)
{
	int		i;
	char	*ret;
	int		len;
	int		j;

	i = 0;
	len = ft_strlen(to_find);
	while (env[i])
	{
		if (ft_strncmp(env[i], to_find, len) == 0 && env[i][len] == '=')
		{
			j = 0;
			while (env[i][j] && env[i][j] != '=')
				j++;
			ret = ft_strdup(&env[i][j + 1]);
			free(to_find);
			if (!ret)
				return (NULL);
			return (ret);
		}
		i++;
	}
	free(to_find);
	return (NULL);
}

int	get_var_name(char *s, size_t i)
{
	i++;
	if (is_valid_char(s[i]) == 0)
		return (-1);
	if (ft_isdigit(s[i]) == 1)
		return (i);
	while (s[i] && is_valid_char(s[i + 1]) == 1)
		i++;
	return (i);
}

int	expand_dquotes_var(char **src, size_t *i, char **env)
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
		s = ft_expand_var(s, *i, env_var, tmp);
		if (!s)
			return (free(tmp), -1);
		*i += ft_strlen(tmp) - 1;
		if (tmp)
			free(tmp);
	}
	*src = s;
	return (0);
}

int	expand_double_quotes(char **src, size_t *i, char **env)
{
	char	*s;

	s = *src;
	s = ft_offset(s, *i);
	while (s[*i] && s[*i] != '"')
	{
		if (s[*i] == '$')
		{
			if (expand_dquotes_var(&s, i, env) == -1)
				return (-1);
		}
		(*i) += 1;
	}
	s = ft_offset(s, *i);
	*src = s;
	return (*i);
}