/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:43:58 by panger            #+#    #+#             */
/*   Updated: 2024/01/15 14:01:56 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_valid_exit(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if ((ft_isdigit(str[i]) == 0))
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi_exit(char *str)
{
	int					i;
	unsigned long long	tot;
	int					minus;

	i = 0;
	tot = 0;
	minus = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus = -1;
		i++;
	}
	while (str[i])
	{
		tot = tot * 10 + (str[i] - '0');
		if (tot > LLONG_MAX)
			return (-1);
		i++;
	}
	i = tot % 256;
	if (minus == -1)
		i = i * -1 + 256;
	return (i);
}

int	builint_exit(t_block *head, char ***env, char **args)
{
	int	ret;

	ret = 0;
	if (ft_tablen(args) > 1)
	{
		if (ft_is_valid_exit(args[1]) == 0 || ft_atoi_exit(args[1]) == -1)
		{
			write(2, "minishell: exit: ", 17);
			write(2, args[1], ft_strlen(args[1]));
			write(2, ": numeric argument required\n", 28);
			free_and_exit(head, *env, 2);
		}
		else if (ft_tablen(args) == 2)
			free_and_exit(head, *env, ft_atoi_exit(args[1]));
		if (ft_tablen(args) > 2)
			write(2, "minishell: exit: too many arguments\n", 36);
		return (1);
	}
	free_and_exit(head, *env, ret);
	return (0);
}
