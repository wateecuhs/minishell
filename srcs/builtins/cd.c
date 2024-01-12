/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:07:51 by panger            #+#    #+#             */
/*   Updated: 2024/01/12 14:11:51 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	case_arg(char **args, char ***env)
{
	char	**tmp;
	int	i;
	int	j;

	i = 0;
	tmp = *env;
	while (ft_strncmp(tmp[i], "OLDPWD=", 7) != 0)
		i++;
	j = 0;
	while (ft_strncmp(tmp[j], "PWD=", 4) != 0)
		j++;
	if (chdir(args[1]) == -1)
		return (perror("minishell:"), 1);
	tmp[i] = ft_strjoin("OLDPWD", &tmp[j][3]);
	free(tmp[j]);
	tmp[j] = ft_strjoin_free2("PWD=", getcwd(NULL, 0));
	*env = tmp;
	return (0);
}

int	case_empty(char ***env)
{
	char	**tmp;
	int	i;
	int	j;
	int	k;

	tmp = *env;
	i = 0;
	while (tmp[i] && ft_strncmp(tmp[i], "OLDPWD=", 7) != 0)
		i++;
	j = 0;
	while (tmp[j] && ft_strncmp(tmp[j], "PWD=", 4) != 0)
		j++;
	k = 0;
	while (tmp[k] && ft_strncmp(tmp[k], "HOME=", 5) != 0)
		k++;
	if (!tmp[k])
		return (write(2, "minishell: cd: HOME not set\n", 28), 1);
	if (chdir(&tmp[k][5]) == -1)
		return (perror("minishell:"), 1);
	tmp[i] = ft_strjoin("OLDPWD", &tmp[j][3]);
	free(tmp[j]);
	tmp[j] = ft_strjoin_free2("PWD=", getcwd(NULL, 0));
	*env = tmp;
	return (0);
}

int	builtin_cd(char **args, char ***env)
{
	char	**tmp;

	tmp = *env;
	if (ft_tablen(args) > 2)
		return (write(2, "minishell: cd: too many arguments\n", 34), 1);
	if (ft_tablen(args) == 2)
		return (case_arg(args, env));
	else
		return (case_empty(env));
	return (0);
}
