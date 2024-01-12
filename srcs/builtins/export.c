/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:43:24 by panger            #+#    #+#             */
/*   Updated: 2024/01/12 16:17:01 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_env(char *string, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] == string[j] && string[j] != '=')
			j++;
		if ((env[i][j] == '\0' || env[i][j] == '=') && string[j] == '=')
			return (2);
		if ((env[i][j] == '\0' && string[j] == '\0') || (env[i][j] == '=' && string[j] == '\0'))
			return (1);
		i++;
	}
	return (0);
}

int	replace_env(char *str, char ***env)
{
	size_t	i;
	size_t	j;

	i = 0;
	while ((*env)[i])
	{
		j = 0;
		while ((*env)[i][j] && (*env)[i][j] == str[j] && str[j] != '=')
			j++;
		if ((*env)[i][j] == '=' || (*env)[i][j] == '\0')
		{
			free((*env)[i]);
			(*env)[i] = ft_strdup(str);
			if (!((*env)[i]))
				return (-1);
		}
		i++;
	}
	return (0);
}

int	add_to_env(char *str, char ***env)
{
	char	**tmp;
	int		len;
	size_t	i;

	len = ft_tablen(*env);
	tmp = (char **)malloc(sizeof(char *) * (len + 2));
	if (!tmp)
		return (-1);
	i = 0;
	while ((*env)[i])
	{
		tmp[i] = ft_strdup((*env)[i]);
		if (!(tmp[i]))
			return (freetabn(tmp, i - 1), -1);
		i++;
	}
	tmp[i++] = ft_strdup(str);
	tmp[i] = NULL;
	*env = tmp;
	return (0);
}

int	print_export(char **env, int fd[2])
{
	size_t	i;
	int		stop;

	i = 0;
	while (env[i])
	{
		write(fd[OUT], "declare -x ", 11);
		stop = ft_strchr(env[i], '=');
		if (stop == -1)
			write(fd[OUT], env[i], ft_strlen(env[i]));
		else
		{
			write(fd[OUT], env[i], stop + 1);
			write(fd[OUT], "\"", 1);
			write(fd[OUT], &env[i][stop + 1], ft_strlen(env[i]) - stop + 1);
			write(fd[OUT], "\"", 1);
		}
		write(fd[OUT], "\n", 1);
		i++;
	}
	return (0);
}

int	builtin_export(char **args, char ***env, int fd[2])
{
	size_t	i;
	int		value;

	if (ft_tablen(args) == 1)
		return (print_export(*env, fd));
	i = 1;
	while (args[i])
	{
		value = in_env(args[i], *env);
		if (value == 2)
			replace_env(args[i], env);
		else if (value == 0)
			add_to_env(args[i], env);
		i++;
	}
	return (0);
}
