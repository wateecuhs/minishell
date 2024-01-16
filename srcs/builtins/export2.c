/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:04:36 by panger            #+#    #+#             */
/*   Updated: 2024/01/16 13:05:20 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_name(char *s)
{
	size_t	i;

	i = 0;
	if (is_valid_char(s[i]) == 0)
		return (-1);
	if (ft_isdigit(s[i]) == 1)
		return (-1);
	while (s[i] && is_valid_char(s[i]) == 1 && s[i] != '=' && s[i] != '\n')
		i++;
	if (s[i] == '\0' || s[i] == '=')
	{
		return (0);
	}
	return (-1);
}
