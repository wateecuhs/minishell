/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:12:09 by waticouz          #+#    #+#             */
/*   Updated: 2024/01/22 11:21:06 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status_code;

int	init_value(char ***env, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	g_status_code = 0;
	if (dup_env(env) == -1)
		return (-1);
	return (0);
}

// Main function for testing
int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_token	*tokens;

	if (init_value(&env, argc, argv) == -1)
		return (1);
	while (1)
	{
		handling_sig(1);
		input = readline("shell42 $ ");
		if (!input)
			return (printf("exit\n"), free_env(env), g_status_code);
		tokens = ft_calloc(1, sizeof(t_token));
		if (tokens == NULL)
			return (free_env(env), 1);
		if (*input)
			add_history(input);
		if (parsing(input, tokens) == 0)
		{
			free(input);
			execution_hub(tokens, &env);
		}
	}
	return (g_status_code);
}
