/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:17:36 by panger            #+#    #+#             */
/*   Updated: 2024/01/22 13:50:00 by panger           ###   ########.fr       */
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
	else
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

int	get_heredoc(char *limiter, char **env, char **hd_data)
{
	char	*tmp;
	int		line;

	g_status_code = 0;
	line = 0;
	*hd_data = NULL;
	handling_sig(3);
	while (1)
	{
		write(2, "> ", 2);
		tmp = get_next_line(0);
		if (ft_strcmp_hd(tmp, limiter) == 0 || tmp == NULL
			|| g_status_code == 130)
			break ;
		expand_heredoc(&tmp, env);
		*hd_data = ft_strjoin_free(*hd_data, tmp);
		free(tmp);
		line++;
	}
	if (g_status_code == 130)
		return (free(tmp), -1);
	if (tmp == NULL)
		return (error_heredoc(limiter, line), free(tmp), 0);
	return (free(tmp), 0);
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
