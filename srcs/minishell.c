/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:12:09 by waticouz          #+#    #+#             */
/*   Updated: 2024/01/09 14:38:32 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Main function for testing
int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_token	*tokens;

	while (1)
	{
		input = readline("\001\e[0;35m\002shell42 $ ");
		write(2, "input is :", 10);
		write(2, input, ft_strlen(input));
		write(2, "\n", 1);
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
		execution_hub(tokens, env);
		free(input);
		lst_free(tokens);
	}
	return (0);
}
