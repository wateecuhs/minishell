/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waticouz <waticouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 18:55:11 by waticouz          #+#    #+#             */
/*   Updated: 2023/12/23 16:35:50 by waticouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
Receiving data as a linked list that has a value and a type
cat is type 0 (word) and its value is "cat"
*/

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
			ret = ft_strndup(&env[i][j + 1], ft_strlen(env[i] - j));
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

int	expand_double_quotes(char *s, size_t i, char **env)
{
	// int		start;
	int		env_var;
	char	*tmp;

	(void)env;
	i ++;
	while (s[i] && s[i] != '"')
	{
		if (s[i] == '$')
		{
			env_var = get_var_name(s, i);
			if (env_var != -1)
			{
				tmp = ft_strndup(&s[i + 1], env_var - i);
				tmp = parse_env(env, tmp);
				if (!tmp)
					s = ft_expand_var(s, i, env_var, tmp);
			}
		}
		i++;
	}
	return (0);
}

int	expand_word(char *s, char **env)
{
	size_t	i;

	i = 0;
	printf("%s\n\n", s);
	(void)env;
	while (s[i])
	{
		// if (s[i] == '\'')
			// expand_single_quotes(s, i);
		if (s[i] == '"')
		{
			expand_double_quotes(s, i, env);
		}
		i++;
	}
	return (0);
}

int	expand(t_token *head, char **env)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
			tmp = tmp->next;
		if (tmp->type == WORD)
			expand_word(tmp->value, env);
		if (tmp)
			tmp = tmp->next;
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	expand_word("echo \"$please test\"", env);
}