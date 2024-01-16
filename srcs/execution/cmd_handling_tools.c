/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handling_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:21:33 by panger            #+#    #+#             */
/*   Updated: 2024/01/16 13:23:44 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_fds(int fd[4], t_block *head, char ***env)
{
	if (fd[2 + IN] == -1 || fd[2 + OUT] == -1)
		free_and_exit(head, *env, 1);
}

int	dup_job(int fd[2])
{
	if (fd[IN] != 0)
	{
		if (dup2(fd[IN], STDIN_FILENO) == -1)
			return (perror_prefix("Broken pipe"), -1);
		close(fd[IN]);
	}
	if (fd[OUT] != 1)
	{
		if (dup2(fd[OUT], STDOUT_FILENO) == -1)
			return (perror_prefix("Broken pipe"), -1);
		close(fd[OUT]);
	}
	return (0);
}

void	remove_empty(char ***env)
{
	int	i;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strchr((*env)[i], '=') == -1)
			(*env)[i] = NULL;
		i++;
	}
}
