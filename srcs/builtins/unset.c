/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:22:51 by panger            #+#    #+#             */
/*   Updated: 2024/01/12 13:35:21 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_args(char *s, char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j] && args[i][j] == s[j])
			j++;
		if (s[j] == '=' && args[i][j] == '\0')
			return (0);
		i++;
	}
	return (1);
}

int	ft_tablen_unset(char **s, char **args)
{
	unsigned int	i;
	unsigned int	count;

	if (!s)
		return (0);
	count = 0;
	i = 0;
	while (s[i])
	{
		if (in_args(s[i], args) != 0)
			count++;
		i++;
	}
	return (count);
}

int	dup_env_unset(char ***env,  char **args)
{
	char	**tmp;
	int		len;
	int		i;

	len = ft_tablen(*env);
	tmp = (char **)malloc(sizeof(char *) * (len + 1));
	if (!tmp)
		return (-1);
	i = 0;
	while ((*env)[i])
	{
		if (in_args((*env)[i], args) != 0)
		{
			printf("%s not in args\n", (*env)[i]);
			tmp[i] = ft_strdup((*env)[i]);
			if (!(tmp[i]))
				return (freetabn(tmp, i - 1), -1);
		}
		free((*env)[i]);
		i++;
	}
	free(*env);
	tmp[i] = NULL;
	*env = tmp;
	return (0);
}

int	builtin_unset(char ***env, char **args)
{
	int	i;

	if (ft_tablen(args) == 1)
		return (0);
	i = 1;
	while (args[i])
	{
		args[i] = expand_word(args[i], *env);
		i++;
	}
	if (dup_env_unset(env, args) == -1)
		return (perror_prefix("unset"), 1);
	return (0);
}