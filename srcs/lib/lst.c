/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:50:07 by dcindrak          #+#    #+#             */
/*   Updated: 2024/01/08 18:39:40 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_free(t_token *lst)
{
	t_token	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->value);
		free(lst);
		lst = tmp;
	}
}

t_token	*lst_new(TokenType type, char *value)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->type = type;
	new->value = value;
	new->next = NULL;
	return (new);
}

t_token	*ft_lstlast(t_token *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	return (lst);
}

int	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (new == NULL)
		return (1);
	if ((*lst)->value == NULL)
	{
		(*lst)->type = new->type;
		(*lst)->value = new->value;
		(*lst)->next = NULL;
		(*lst)->prev = NULL;
		free(new);
		return (0);
	}
	tmp = ft_lstlast(*lst);
	tmp->next = new;
	new->prev = tmp;
	return (0);
}
