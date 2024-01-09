/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:07:51 by panger            #+#    #+#             */
/*   Updated: 2024/01/09 15:19:27 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(char **env)
{
	char	*tmp;
	int	i;
	int	j;

	i = 0;
	while (ft_strncmp(env[i], "OLDPWD=", 7) != 0)
		i++;
	while (ft_strncmp(env[j], "PWD=", 4) != 0)
		j++;
	
	tmp = getcwd(NULL, 0);
}