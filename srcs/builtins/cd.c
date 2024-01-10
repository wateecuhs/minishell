/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:07:51 by panger            #+#    #+#             */
/*   Updated: 2024/01/10 18:13:44 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(char **args, char ***env)
{
	char	**tmp;
	int	i;
	int	j;

	i = 0;
	tmp = *env;
	if (ft_tablen(args) > 2)
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		return (1);
	}
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
