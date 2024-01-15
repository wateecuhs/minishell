/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:57:59 by dcindrak          #+#    #+#             */
/*   Updated: 2024/01/15 12:41:47 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_handler(int sig)
{
	if (sig == SIGINT) // ctrl + c et code = 130
	{
		g_status_code = 130;
		ioctl(0, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	else if (sig == SIGQUIT) // ctrl + backslash
	{
		signal(SIGQUIT, SIG_IGN); // do nothing
	}
}

static void	sig_heredoc_handler(int sig)
{
	if (sig == SIGINT) // ctrl + c et code = 130
	{
		g_status_code = 130;
		ioctl(0, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	else if (sig == SIGQUIT) // ctrl + backslash
	{
		signal(SIGQUIT, SIG_IGN); // do nothing
	}
}

static void	sig_child_handler(int sig)
{
	if (sig == SIGINT) // ctrl + c et code = 130
	{
		g_status_code = 130;
		ioctl(0, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	else if (sig == SIGQUIT) // ctrl + backslash 131
	{
		fprintf(stderr, "Quit: 3\n");
	}
}

void	handling_sig(int mod)
{
	if(mod == 1) // interactive
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN); // do nothing
	}
	if (mod == 2) // child
	{
		signal(SIGINT, sig_child_handler);
		signal(SIGQUIT, SIG_DFL); // need to end child process
	}
	if (mod == 3) // here doc
	{
		signal(SIGINT, sig_heredoc_handler);
		signal(SIGQUIT, SIG_IGN); // 
	}
}