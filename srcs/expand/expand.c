/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waticouz <waticouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 18:55:11 by waticouz          #+#    #+#             */
/*   Updated: 2023/12/22 23:28:10 by waticouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
Receiving data as a linked list that has a value and a type
cat is type 0 (word) and its value is "cat"
*/

#include "minishell.h"

char	*parse_env(char **env, char *to_find)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], to_find, ft_strlen(to_find)) == 0)
		{
			return ;
		}
		i++;
	}
	return (NULL);
}

int	get_variable(char *s, char **env)
{
	size_t		i;
	char	*tmp;

	i = 0;
	while (s[i] && is_whitespace(s[i] == 0))
		i++;
	tmp = (char *)malloc(sizeof(char) * (i + 2));
	if (!tmp)
		return (-1);
	i = 0;
	while (s[i] && is_whitespace(s[i] == 0))
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i++] = '=';
	tmp[i] = '\0';
	
}

void	expand_double_quotes(char *s, size_t *i, char **env)
{
	while (s[*i] && s[*i] != '"')
	{
		if (s[*i] == '$')
			get_variable(&s[*i], env);
		(*i)++;
	}
}

int	expand_word(char *s, char **env)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			expand_single_quotes(s, &i);
		else if (s[i] == '"')
			expand_double_quotes(s, &i, env);
		i++;
	}
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
}