/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:49:30 by panger            #+#    #+#             */
/*   Updated: 2024/01/09 13:53:48 by panger           ###   ########.fr       */
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
			paths = ft_split_s(&env[i][5], ":");
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

char	*find_path(char *cmd, char **env)
{
	int		j;
	char	**paths;
	char	*temp;
	int		found;

	found = 0;
	j = 0;
	if (access(cmd, F_OK) != -1)
	{
		return (cmd);
	}
	paths = get_paths(env);
	while (paths[j] && found == 0)
	{
		temp = join_paths(paths[j++], cmd);
		if (access(temp, F_OK) != -1 && access(temp, X_OK) != -1)
			found = 1;
		else
			free(temp);
	}
	if (found == 1)
		return (freetab(paths), temp);
	freetab(paths);
	return (NULL);
}
