/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:12:09 by waticouz          #+#    #+#             */
/*   Updated: 2024/01/11 16:54:38 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_status_code;

// Main function for testing
int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_token	*tokens;

	g_status_code = 0;
	if (dup_env(&env) == -1)
		return (perror("minishell"), 1);
	while (1)
	{
		input = readline("shell42 $ ");
		tokens = ft_calloc(1, sizeof(t_token));
		if (tokens == NULL)
			return (1);
		if (parsing(input, tokens) == 1)
		{
			//free(tokens);
			//rl_clear_history();
			//return (1);
		}
		if (*input)
			add_history(input);
		execution_hub(tokens, &env);
		free(input);
		lst_free(tokens);
	}
	return (0);
}
