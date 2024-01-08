/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:27:00 by panger            #+#    #+#             */
/*   Updated: 2024/01/08 18:24:34 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handling_sigint(int sig)
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

void free_tokens(t_token *tokens)
{
    t_token *tmp;

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

// Main function for testing
int	main(void)
{
	char	*input;
	t_token	*tokens;
	while(1) // != "exit")
	{
		signal(SIGINT, handling_sigint);
		signal(SIGQUIT, SIG_IGN);
		input = readline("@minishell $");
		if(check_unclosed(input) == 1)
			exit(EXIT_FAILURE); // unclosed quote + free
		if(check_if_broken_enum(input) == 1)
			exit(EXIT_FAILURE); // broken enum + free
		tokens = ft_calloc(1, sizeof(t_token));
		if (tokens == NULL)
			exit(EXIT_FAILURE);
		if (tokenize(&tokens, input) == 1)
		{
			lst_free(tokens);
			return (1);
		}
		add_history(input);
		print_lst(tokens);
		free(input);
		lst_free(tokens);
	}
	return (0);
}