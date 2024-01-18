/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:22:51 by panger            #+#    #+#             */
/*   Updated: 2024/01/18 13:47:40 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_args(char *env_str, char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (env_str[j] && args[i][j] == env_str[j] && env_str[j] != '=')
			j++;
		if ((env_str[j] == '\0' || env_str[j] == '=') && args[i][j] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int	dup_env_unset(char ***env, char **args)
{
	char	**tmp;
	int		len;
	int		i;
	int		j;

	len = ft_tablen(*env);
	tmp = (char **)malloc(sizeof(char *) * (len + 1));
	if (!tmp)
		return (perror_prefix("malloc"), -1);
	i = 0;
	j = 0;
	while ((*env)[i])
	{
		if (in_args((*env)[i], args) == 0)
		{
			tmp[j++] = ft_strdup((*env)[i]);
			if (!(tmp[j - 1]))
				return (freetabn(tmp, j - 2), -1);
		}
		i++;
	}
	tmp[j] = NULL;
	free_env(*env);
	*env = tmp;
	return (0);
}

int	check_name_unset(char *s)
{
	size_t	i;

	i = 0;
	if (is_valid_char(s[i]) == 0)
		return (-1);
	if (ft_isdigit(s[i]) == 1)
		return (-1);
	while (s[i] && is_valid_char(s[i]) == 1 && s[i] != '=' && s[i] != '\n')
		i++;
	if (s[i] == '\0')
		return (0);
	return (-1);
}

int	builtin_unset(char ***env, char **args, int fd[2])
{
	size_t	i;
	int		exit_code;

	if (ft_tablen(args) == 1)
		return (0);
	i = 1;
	exit_code = 0;
	while (args[i])
	{
		if (check_name_unset(args[i]) == -1)
		{
			write(fd[OUT], "bash: unset: '", 14);
			write(fd[OUT], args[i], ft_strlen(args[i]));
			write(fd[OUT], "': not a valid identifier\n", 27);
			exit_code = 1;
		}
		i++;
	}
	if (dup_env_unset(env, &args[1]) == -1)
		return (1);
	return (exit_code);
}
