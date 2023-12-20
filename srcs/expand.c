/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waticouz <waticouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 18:55:11 by waticouz          #+#    #+#             */
/*   Updated: 2023/12/20 19:18:40 by waticouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
Receiving data as a linked list that has a value and a type
cat is type 0 (word) and its value is "cat"
*/

#include "minishell.h"

int	expand_word(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			get_variable(&s[i]);
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
		if (tmp->type == WORD || tmp->type == DOUBLE_QUOTE)
			expand_word(tmp->value);
		if (tmp)
			tmp = tmp->next;
	}
}