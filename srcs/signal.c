/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:57:59 by dcindrak          #+#    #+#             */
/*   Updated: 2024/01/17 15:51:11 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

static void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_status_code = 130;
		write(0, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	sig_child_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_status_code = 130;
		write(0, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

static void	sig_heredoc_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_status_code = 130;
		write(0, "\n", 1);
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
	struct sigaction sa;

	if (mod == 1)
	{
		sa.sa_handler = sig_handler;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		sigaction(SIGINT, &sa, NULL);
		signal(SIGQUIT, SIG_IGN);
	}
	if (mod == 2)
	{
		sa.sa_handler = sig_child_handler;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
	if (mod == 3)
	{
		sa.sa_handler = sig_heredoc_handler;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		sigaction(SIGINT, &sa, NULL);
		signal(SIGQUIT, SIG_IGN);
	}
}
