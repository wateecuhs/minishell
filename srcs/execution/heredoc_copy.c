/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc copy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:17:36 by panger            #+#    #+#             */
/*   Updated: 2024/01/17 12:03:43 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putchar(char c)
{
	write(STDERR_FILENO, &c, 1);
}

void	ft_putnbr(unsigned int nb)
{
	if (nb > 9)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else if (nb >= 0)
		ft_putchar(nb + 48);
}

static void	error_heredoc(char *limiter, int line)
{
	write(2, "minishell : warning: here-document at line ", 43);
	ft_putnbr(line);
	write(2, " delimited by end-of-file (wanted '", 35);
	write(2, limiter, ft_strlen(limiter));
	write(2, "')\n", 3);
}

int	get_heredoc(char *limiter)
{
	char	*string;
	int		p[2];
	int		line;

	pipe(p);
	g_status_code = 0;
	line = 0;
	while (1)
	{
		string = get_next_line(0);
		if (ft_strcmp_hd(string, limiter) == 0 || string == NULL || g_status_code == 130)
			break ;
		write(p[WRITE], string, ft_strlen(string));
		free(string);
		line++;
	}
	close(p[WRITE]);
	if (g_status_code == 130)
		return (free(string), -1);
	if (string == NULL)
		return (error_heredoc(limiter, line), free(string), p[READ]);
	return (free(string), p[READ]);
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