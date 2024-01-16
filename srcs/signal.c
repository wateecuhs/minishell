/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:57:59 by dcindrak          #+#    #+#             */
/*   Updated: 2024/01/16 13:15:11 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_status_code = 130;
		ioctl(0, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

static void	sig_heredoc_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_status_code = 130;
		ioctl(0, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

static void	sig_child_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_status_code = 130;
		ioctl(0, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	else if (sig == SIGQUIT)
	{
		g_status_code = 131;
		write(2, "Quit (core dumped)\n", 19);
	}
}

void	handling_sig(int mod)
{
	if (mod == 1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	if (mod == 2)
	{
		signal(SIGINT, sig_child_handler);
		signal(SIGQUIT, sig_child_handler);
	}
	if (mod == 3)
	{
		signal(SIGINT, sig_heredoc_handler);
		signal(SIGQUIT, SIG_IGN);
	}
}
