/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:07:51 by panger            #+#    #+#             */
/*   Updated: 2024/01/18 16:50:53 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pop_from_env(char ***env, char *str)
{
	char	**tmp;
	int		i;
	int		j;

	tmp = (char **)malloc(sizeof(char *) * (ft_tablen(*env) + 1));
	if (!tmp)
		return (perror_prefix("malloc"), -1);
	i = 0;
	j = 0;
	while ((*env)[i])
	{
		if (is_line_to_pop((*env)[i], str) == 0)
		{
			tmp[j++] = ft_strdup((*env)[i]);
			if (!(tmp[j - 1]))
				return (freetab(tmp), -1);
		}
		i++;
	}
	tmp[j] = NULL;
	free_env(*env);
	*env = tmp;
	return (0);
}

int	add_to_env_cd(char *str, char ***env)
{
	char	**tmp;
	int		len;
	size_t	i;

	if (!str)
		return (0);
	len = ft_tablen(*env);
	tmp = (char **)malloc(sizeof(char *) * (len + 2));
	if (!tmp)
		return (perror_prefix("malloc"), -1);
	i = 0;
	while ((*env)[i])
	{
		tmp[i] = ft_strdup((*env)[i]);
		if (!(tmp[i]))
			return (freetab(tmp), -1);
		i++;
	}
	tmp[i++] = ft_strdup(str);
	if (!tmp[i - 1])
		return (freetab(tmp), free(str), -1);
	tmp[i] = NULL;
	free_env(*env);
	*env = tmp;
	return (free(str), 0);
}

int	case_arg(char *path, char ***env)
{
	char	**pwd;

	if (chdir(path) == -1)
		return (perror_prefix(path), 1);
	if (pop_from_env(env, "OLDPWD") == -1)
		return (1);
	pwd = find_in_env("PWD", *env);
	if (pwd)
	{
		if (add_to_env_cd(ft_strjoin("OLDPWD", &(*pwd)[3]), env) == -1)
			return (1);
	}
	if (pop_from_env(env, "PWD") == -1)
		return (1);
	if (add_to_env_cd(ft_strjoin_free2("PWD=", getcwd(NULL, 0)), env) == -1)
		return (1);
	return (0);
}

int	case_empty(char ***env)
{
	char	**pwd;
	char	**home;

	home = find_in_env("HOME", *env);
	if (!home)
		return (write(2, "minishell: cd: HOME not set\n", 28), 1);
	if (chdir(&(*home)[5]) == -1)
		return (perror_prefix(&(*home)[5]), 1);
	if (pop_from_env(env, "OLDPWD") == -1)
		return (1);
	pwd = find_in_env("PWD", *env);
	if (add_to_env_cd(ft_strjoin("OLDPWD", &(*pwd)[3]), env) == -1)
		return (1);
	if (pop_from_env(env, "PWD") == -1)
		return (1);
	home = find_in_env("HOME", *env);
	if (add_to_env_cd(ft_strjoin("PWD", &(*home)[4]), env) == -1)
		return (1);
	return (0);
}

int	builtin_cd(char **args, char ***env)
{
	char	**tmp_oldpwd;

	if (ft_tablen(args) > 2)
		return (write(2, "minishell: cd: too many arguments\n", 34), 1);
	if (ft_tablen(args) == 2)
	{
		if (ft_strcmp(args[1], "~") == 0)
			return (case_empty(env));
		else if (ft_strcmp(args[1], "-") == 0)
		{
			tmp_oldpwd = find_in_env("OLDPWD", *env);
			if (!tmp_oldpwd)
				return (write(2, "minishell: cd: OLDPWD not set\n", 30), 1);
			return (case_arg((&(*tmp_oldpwd)[7]), env));
		}
		return (case_arg(args[1], env));
	}
	else
		return (case_empty(env));
	return (0);
}
