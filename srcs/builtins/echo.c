/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:56:55 by panger            #+#    #+#             */
/*   Updated: 2024/01/12 15:20:02 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(char **args,int fd[2])
{
	int	i;
	int	nl;

	nl = 0;
	if (ft_tablen(args) <= 1)
		return (write(fd[OUT], "\n", 1), 0);
	i = 1;
	if (ft_strcmp(args[1], "-n") == 0)
	{
		nl = 1;
		i++;
	}
	while (args[i])
	{
		write(fd[OUT], args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(fd[OUT], " ", 1);
		i++;
	}
	if (nl == 0)
		write(fd[OUT], "\n", 1);
	return (0);
}
