/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waticouz <waticouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 15:49:35 by waticouz          #+#    #+#             */
/*   Updated: 2023/12/29 15:59:48 by waticouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths(char **env)
{
	char	**paths;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			paths = ft_split(&env[i][5], ":");
		}
		i++;
	}
	return (paths);
}

char	*join_paths(char *s1, char *s2)
{
	char	*ret;
	char	*temp;
	char	*temp2;
	int		i;

	temp2 = ft_strjoin(s1, "/");
	temp = ft_strdup(s2);
	i = 0;
	while (temp[i] && temp[i] != ' ')
		i++;
	if (temp[i])
		temp[i] = '\0';
	ret = ft_strjoin(temp2, temp);
	free(temp2);
	free(temp);
	return (ret);
}
