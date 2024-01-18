/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:04:36 by panger            #+#    #+#             */
/*   Updated: 2024/01/18 13:46:04 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	non_valid_identifier(char *str)
{
	if (check_name(str) == -1)
	{
		write(2, "minishell: export: '", 20);
		write(2, str, ft_strlen(str));
		write(2, "': not a valid identifier\n", 27);
		return (1);
	}
	return (0);
}

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

char	**sort_env(char **env)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[j])
		{
			if (i != j && ft_strcmp(env[i], env[j]) < 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (env);
}
