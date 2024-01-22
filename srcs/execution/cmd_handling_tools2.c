/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handling_tools2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:21:33 by panger            #+#    #+#             */
/*   Updated: 2024/01/22 12:13:49 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_fds(int fd[4], t_block *head, char ***env)
{
	if (fd[2 + IN] == -1 || fd[2 + OUT] == -1)
		free_and_exit(head, *env, 1);
}

int	is_hd(t_redirs *redirs)
{
	int	redir;

	redir = 0;
	while (redirs)
	{
		if (redirs->type == HEREDOC)
			redir = 1;
		if (redirs->type == REDIRECT_IN)
			redir = 0;
		redirs = redirs->next;
	}
	return (redir);
}
