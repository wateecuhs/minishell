/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parse2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:26:59 by panger            #+#    #+#             */
/*   Updated: 2024/01/12 10:27:48 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_name(char *s)
{
	size_t	i;

	i = 0;
	/*if (ft_isdigit(s[i]) == 1)
		return (-1);
	if (is_valid_char(s[i]) == 0)
		return (-1);*/
	if (char_valid(s) == 1)
		return (-1);
	while (s[i] && s[i] != '=' && s[i] != '\n')
		i++;
	if (s[i] == '\0' || s[i] == '=')
	{
		return (0);
	}
	return (-1);
}

void	no_args(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
		printf("declare -x \"%s\"\n", env[i++]);
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

int	export(char *str, char ***env)
{
	int		i;
	char	*tmp;
	int		fd;

	tmp = expand_word(str, *env);
	if (!tmp)
		return (-1);
	i = 0;
	if (check_name(tmp) == -1)
	{
		fd = dup(1);
		dup2(2, 1);
		printf("bash: export: '%s': not a valid identifier\n", tmp);
		dup2(fd, 1);
		return (0);
	}
	if (add_to_env(tmp, env) == -1)
		return (-1);
	return (0);
}

int	builtin_export(char **args, char ***env, int fds[4])
{
	int		i;

	if (ft_tablen(args) == 1)
		no_args(*env);
	else
	{
		i = 1;
		while (args[i])
		{
			export(args[i], env);
			i++;
		}
	}
	// builtin_env(NULL, env);
	return (0);
}