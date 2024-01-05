/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 18:55:11 by waticouz          #+#    #+#             */
/*   Updated: 2024/01/05 16:16:30 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_word(char *s, char **env)
{
	size_t	i;
	int		val;

	i = 0;
	(void)env;
	while (s[i])
	{
		if (s[i] == '\'')
			expand_single_quotes(&s, &i);
		if (s[i] == '"')
		{
			val = expand_double_quotes(&s, &i, env);
			if (val == -1)
				return (free(s), NULL);
			i = val;
		}
		i++;
	}
	return (s);
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
		{
			tmp->value = expand_word(tmp->value, env);
			if (tmp->value == NULL)
				return (-1);
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char	*tmp = ft_strdup("echo $|ok \"$test $rien $|ok test\" \'$test $rien $nothing test\'");
	printf("expanding:\n%s\n", tmp);
	tmp = expand_word(tmp, env);
	printf("expanded:\n%s\n", tmp);
	free(tmp);
}