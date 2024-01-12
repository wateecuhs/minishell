/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:21:36 by panger            #+#    #+#             */
/*   Updated: 2024/01/12 12:49:36 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_block *blocks, char ***env, int fds[4], t_block *head)
{
	if (strcmp(blocks->cmd, "echo") == 0)
		return (builtin_echo(blocks->args, *env));
	else if (strcmp(blocks->cmd, "cd") == 0)
		return (builtin_cd(blocks->args, env));
	else if (strcmp(blocks->cmd, "pwd") == 0)
		return (builtin_pwd());
	else if (strcmp(blocks->cmd, "export") == 0)
		return (builtin_export(blocks->args, env, fds));
	else if (strcmp(blocks->cmd, "unset") == 0)
		return (builtin_unset(env, blocks->args));
	else if (strcmp(blocks->cmd, "env") == 0)
		return (builtin_env(fds, env));
	else if (strcmp(blocks->cmd, "exit") == 0)
		return (builint_exit(head, env));
	else
		return (-1);
	if (blocks->next)
		return (-2);
	return (0);
}
