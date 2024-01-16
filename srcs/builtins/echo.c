/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:56:55 by panger            #+#    #+#             */
/*   Updated: 2024/01/16 13:06:14 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_n(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	if (i == 0)
		return (0);
	return (1);
}

int	builtin_echo(char **args, int fd[2])
{
	int	i;
	int	nl;

	nl = 0;
	if (ft_tablen(args) <= 1)
		return (write(fd[OUT], "\n", 1), 0);
	i = 1;
	if (args[1][0] == '-' && is_n(&args[1][1]))
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
