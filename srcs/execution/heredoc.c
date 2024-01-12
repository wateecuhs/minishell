/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:17:36 by panger            #+#    #+#             */
/*   Updated: 2024/01/12 14:50:50 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_heredoc(char *limiter)
{
	char	*string;
	int		p[2];

	pipe(p);
	string = get_next_line(0);
	while (string != NULL && ft_strcmp_hd(string, limiter) != 0)
	{
		if (write(p[WRITE], string, ft_strlen(string)) == -1)
			printf("pipex: write error: %s\n", strerror(errno));
		free(string);
		string = get_next_line(0);
	}
	free(string);
	close(p[WRITE]);
	return (p[READ]);
}

char	*has_heredoc(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == HEREDOC)
			return (tokens->next->value);
		tokens = tokens->next;
	}
	return (NULL);
}