/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:21:36 by panger            #+#    #+#             */
/*   Updated: 2024/01/10 16:36:57 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_block *blocks, char ***env, int *code)
{
	if (strcmp(blocks->cmd, "echewo") == 0)
		return (1);
	else if (strcmp(blocks->cmd, "cd") == 0)
		*code = builtin_cd(blocks->args, env);
	else if (strcmp(blocks->cmd, "pwqwed") == 0)
		return (3);
	else if (strcmp(blocks->cmd, "eqwexport") == 0)
		return (4);
	else if (strcmp(blocks->cmd, "unqweset") == 0)
		return (5);
	else if (strcmp(blocks->cmd, "eqwenv") == 0)
		return (6);
	else if (strcmp(blocks->cmd, "exiqwet") == 0)
		return (7);
	else
		return (-1);
	if (blocks->next)
		*code = -1;
	return (0);
}
