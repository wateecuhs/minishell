/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:05:44 by waticouz          #+#    #+#             */
/*   Updated: 2024/01/08 16:57:57 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*set_fd(int *fd_in_out, char *infile, char *outfile)
{
	fd_in_out[IN] = open(infile, O_RDONLY);
	if (fd_in_out[IN] == -1)
		perror(infile);
	fd_in_out[OUT] = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_in_out[OUT] == -1)
		perror(outfile);
	return (fd_in_out);
}

int	*set_fd_heredoc(int *fd_in_out, char *limiter, char *outfile)
{
	char	*string;
	int		p[2];

	pipe(p);
	string = get_next_line(0);
	while (ft_strcmp_hd(string, limiter) != 0 && string != NULL)
	{
		if (write(p[WRITE], string, ft_strlen(string)) == -1)
			ft_printf("minishell: write error: %s\n", strerror(errno));
		string = get_next_line(0);
	}
	close(p[WRITE]);
	fd_in_out[IN] = p[READ];
	fd_in_out[OUT] = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd_in_out[OUT] == -1)
		perror(outfile);
	return (fd_in_out);
}
