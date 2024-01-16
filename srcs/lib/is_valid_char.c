/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 15:02:05 by waticouz          #+#    #+#             */
/*   Updated: 2024/01/16 13:11:06 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_char(int c)
{
	if (c == '_' || ft_isalnum(c) == 1)
		return (1);
	return (0);
}

int	char_valid(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '=')
		return (1);
	if (ft_isdigit(s[i]) == 1)
		return (1);
	while (s[i] != '=' && s[i])
	{
		if (s[i] == '_' || ft_isalnum(s[i]) == 1)
			i++;
		else
			return (1);
	}
	return (0);
}
