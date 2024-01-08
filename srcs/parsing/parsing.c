/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcindrak <dcindrak@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:52:47 by dcindrak          #+#    #+#             */
/*   Updated: 2024/01/07 16:58:18 by dcindrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handling_sigint(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(0, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	else if (sig == SIGQUIT)
	{
		printf("Quit: 3\n");
	}
	else if (sig == SIGHUP)
	{
		// Handle CTRL+D (SIGHUP) signal
	}
}

/*int builtins(char *str, char **env)
{
	char **cmd;
	cmd = ft_split(str, ' ');
	if (ft_strncmp(str, "pwd", 3) == 0)
		return (ft_pwd());
	if (ft_strncmp(str, "echo", 4) == 0)
		return (ft_echo(cmd, str));
	if (ft_strncmp(str, "env", 3) == 0)
		return (ft_env(env));
	if (ft_strncmp(str, "export", 6) == 0)
		return (ft_export(cmd, env));
	if (ft_strncmp(str, "unset", 5) == 0)
		return (ft_unset(cmd, env));
	if (ft_strncmp(str, "cd", 2) == 0)
		return (ft_cd(cmd, env));
	if (ft_strncmp(str, "exit", 4) == 0)
		return (ft_exit(cmd));
	return (1);
}*/

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		free(tmp->value);
		tmp = tmp->next;
	}
	free(tokens);
}

void	print_lst(t_token *lst)
{
	t_token	*tmp;

	tmp = lst;
	while (tmp)
	{
		printf("type: %d, value: %s\n", tmp->type, tmp->value);
		tmp = tmp->next;
	}
}

int	parsing(char *input, t_token *tokens)
{
	signal(SIGINT, handling_sigint);
	signal(SIGQUIT, SIG_IGN);
	if (check_unclosed(input) == 1)
		return (1);
	if (check_if_broken_enum(input) == 1)
		return (1);
	if (tokenize(&tokens, input) == 1)
	{
		lst_free(tokens);
		return (1);
	}
	return (0);
}
