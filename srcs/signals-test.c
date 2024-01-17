/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals-test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:57:59 by dcindrak          #+#    #+#             */
/*   Updated: 2024/01/17 12:25:32 by panger           ###   ########.fr       */
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
		
		if (isatty(1) == 1)
		{
			g_status_code = 130;
			write(0, "\n", 1);
			rl_replace_line("", 0);
		}
	}
	else if (sig == SIGQUIT)
	{
		if (isatty(1) == 1)
		{
			write(0, "Quit (core dumped)\n", 19);
			g_status_code = 131;
		}
		else
			signal(SIGQUIT, SIG_IGN);
	}
}

static void	sig_heredoc_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_status_code = 130;
		write(0, "\n", 1);
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
