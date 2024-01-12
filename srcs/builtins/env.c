/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:42:00 by panger            #+#    #+#             */
/*   Updated: 2024/01/12 15:08:08 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(int fd[2], char ***env)
{
	int	i;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strchr((*env)[i], '=') != -1)
		{
			write(fd[WRITE], (*env)[i], ft_strlen((*env)[i]));
			write(fd[WRITE], "\n", 1);
		}
		i++;
	}
	return (0);
}