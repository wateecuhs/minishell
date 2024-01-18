/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcindrak <dcindrak@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:52:47 by dcindrak          #+#    #+#             */
/*   Updated: 2024/01/18 14:35:35 by dcindrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

static int	checkascii(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (ft_isascii(input[i]) == 0)
		{
			write(2, "minishell: syntax error near unexpected token `", 47);
			write(2, &input[i], 1);
			write(2, "'\n", 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int	parsing(char *input, t_token *tokens)
{
	if (checkascii(input) == 1)
	{
		lst_free(tokens);
		g_status_code = 2;
		return (1);
	}
	if (check_unclosed(input) == 1)
	{
		lst_free(tokens);
		g_status_code = 2;
		return (1);
	}
	if (check_if_broken_enum(input) == 1)
	{
		lst_free(tokens);
		g_status_code = 2;
		return (1);
	}
	if (tokenize(&tokens, input) == 1)
	{
		lst_free(tokens);
		g_status_code = 2;
		return (1);
	}
	return (0);
}
