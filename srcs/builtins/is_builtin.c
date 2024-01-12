/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:21:36 by panger            #+#    #+#             */
/*   Updated: 2024/01/12 16:14:52 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_cmd_builtin(char *cmd)
{
	if (!cmd)
		return (-1);
	if (strcmp(cmd, "echo") == 0)
		return (0);
	else if (strcmp(cmd, "cd") == 0)
		return (0);
	else if (strcmp(cmd, "pwd") == 0)
		return (0);
	else if (strcmp(cmd, "export") == 0)
		return (0);
	else if (strcmp(cmd, "unset") == 0)
		return (0);
	else if (strcmp(cmd, "env") == 0)
		return (0);
	else if (strcmp(cmd, "exit") == 0)
		return (0);
	else
		return (-1);
}

int	exec_builtin(t_block *blocks, char ***env, int fds[4], t_block *head)
{
	if (strcmp(blocks->cmd, "echo") == 0)
		return (builtin_echo(blocks->args, &fds[2]));
	else if (strcmp(blocks->cmd, "cd") == 0)
		return (builtin_cd(blocks->args, env));
	else if (strcmp(blocks->cmd, "pwd") == 0)
		return (builtin_pwd(&fds[2]));
	else if (strcmp(blocks->cmd, "export") == 0)
		return (builtin_export(blocks->args, env, &fds[2]));
	else if (strcmp(blocks->cmd, "unset") == 0)
		return (builtin_unset(env, blocks->args));
	else if (strcmp(blocks->cmd, "env") == 0)
		return (builtin_env(&fds[2], env));
	else if (strcmp(blocks->cmd, "exit") == 0)
		return (builint_exit(head, env));
	return (0);
}
