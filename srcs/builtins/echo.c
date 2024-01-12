/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:56:55 by panger            #+#    #+#             */
/*   Updated: 2024/01/12 10:23:03 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(char **args, char **env)
{
	int	i;
	int	nl;

	nl = 0;
	if (ft_tablen(args) <= 1)
		return (printf("\n") ,0);
	i = 1;
	if (ft_strcmp(args[1], "-n") == 0)
	{
		nl = 1;
		i++;
	}
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (nl == 0)
		printf("\n");
	return (0);
}
