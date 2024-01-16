/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:37:02 by panger            #+#    #+#             */
/*   Updated: 2024/01/16 13:37:50 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_line_to_pop(char *env_line, char *str)
{
	int	k;

	k = 0;
	while (env_line[k] && env_line[k] == str[k] && str[k] != '=')
		k++;
	if (!(env_line[k] == '=' || env_line[k] == '\0'))
	{
		return (0);
	}
	return (1);
}
