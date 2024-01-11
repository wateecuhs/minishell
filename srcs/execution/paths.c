/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:49:30 by panger            #+#    #+#             */
/*   Updated: 2024/01/11 17:22:28 by panger           ###   ########.fr       */
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

void	handle_error(char *cmd)
{
	int	tmp;

	if (errno == 13)
		perror_prefix(cmd);
	else
	{
		write(2, "minishell: ", 11);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": command not found\n", 20);
	}
}

char	*find_path(char *cmd, char **env)
{
	int		j;
	char	**paths;
	char	*temp;

	j = 0;
	if (ft_strchr(cmd, '/') != -1)
	{
		if (access(cmd, F_OK) != -1 && access(cmd, X_OK) != -1)
			return (cmd);
		return (handle_error(cmd), NULL);
	}
	paths = get_paths(env);
	while (paths[j])
	{
		temp = join_paths(paths[j++], cmd);
		if (access(temp, F_OK) != -1 && access(temp, X_OK) != -1)
				return (freetab(paths), temp);
		free(temp);
	}
	freetab(paths);
	handle_error(cmd);
	return (NULL);
}
