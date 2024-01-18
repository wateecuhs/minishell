/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:49:30 by panger            #+#    #+#             */
/*   Updated: 2024/01/18 18:40:34 by panger           ###   ########.fr       */
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
			return (paths);
		}
		i++;
	}
	return (NULL);
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
	while (temp[i])
		i++;
	if (temp[i])
		temp[i] = '\0';
	ret = ft_strjoin(temp2, temp);
	free(temp2);
	free(temp);
	return (ret);
}

int	is_dir(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) == -1)
		return (0);
	if (S_ISDIR(statbuf.st_mode) == 1)
		return (1);
	return (0);
}

void	handle_error(char *cmd, int err, int *exit_code)
{
	if (err == 0 && is_dir(cmd) == 1)
	{
		write(2, "minishell: ", 11);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": Is a directory\n", 17);
		*exit_code = 126;
	}
	else if (errno == 13 && err == 0)
	{
		perror_prefix(cmd);
		*exit_code = 126;
	}
	else if (err == 0)
	{
		perror_prefix(cmd);
		*exit_code = 127;
	}
	else
	{
		write(2, "minishell: ", 11);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": command not found\n", 20);
		*exit_code = 127;
	}
	free(cmd);
}

char	*find_path(char *cmd, char **env, int *exit_code)
{
	int			j;
	char		**paths;
	char		*temp;

	j = 0;
	if (ft_strchr(cmd, '/') != -1)
	{
		if (access(cmd, F_OK) != -1 && access(cmd, X_OK) != -1
			&& is_dir(cmd) != 1)
			return (cmd);
		return (handle_error(cmd, 0, exit_code), NULL);
	}
	paths = get_paths(env);
	if (!paths)
		return (handle_error(cmd, 1, exit_code), NULL);
	while (paths[j])
	{
		temp = join_paths(paths[j++], cmd);
		if (!temp || (access(temp, F_OK) != -1 && access(temp, X_OK) != -1
				&& is_dir(temp) != 1))
			return (freetab(paths), free(cmd), temp);
		free(temp);
	}
	return (freetab(paths), handle_error(cmd, 1, exit_code), NULL);
}
