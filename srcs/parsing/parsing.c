/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:52:47 by dcindrak          #+#    #+#             */
/*   Updated: 2024/01/16 13:07:43 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(char *input, t_token *tokens)
{
	if (check_unclosed(input) == 1)
	{
		lst_free(tokens);
		return (1);
	}
	if (check_if_broken_enum(input) == 1)
	{
		lst_free(tokens);
		return (1);
	}
	if (tokenize(&tokens, input) == 1)
	{
		lst_free(tokens);
		return (1);
	}
	return (0);
}
