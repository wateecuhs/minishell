/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_in_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:36:52 by panger            #+#    #+#             */
/*   Updated: 2024/01/12 18:38:52 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_in_env(char *str, char **env)
{
	size_t	i;
	size_t	equal_pos;

	i = 0;
	while (env[i])
	{
		equal_pos = ft_strchr(env[i], '=');
		if (equal_pos != -1)
		{
			if (ft_strncmp(env[i], str, equal_pos) == 0)
				return (env[i]);
		}
		i++;
	}
	return (NULL);
}
