/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waticouz <waticouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:34:56 by panger            #+#    #+#             */
/*   Updated: 2023/12/29 16:14:22 by waticouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 100000
#endif

char	*cut_str(char *str)
{
	char	*ret;	

	if (ft_strchr(str, '\n') == -1)
	{
		ret = ft_strdup(str);
		free(str);
		if (!ret)
			return (NULL);
		return (ret);
	}
	else
	{
		ret = ft_strdupset(str, 0, ft_strchr(str, '\n') + 1);
		free(str);
		if (!ret)
			return (NULL);
		return (ret);
	}
}

int	testing(char (*buffer)[BUFFER_SIZE + 1], char **str)
{
	int	i;
	int	j;

	i = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	if (!((*buffer)[i] == '\n' && (*buffer)[i + 1] == '\0'))
	{
		i++;
		*str = ft_stradd(*str, &(*buffer)[i], BUFFER_SIZE - i);
		if (!(*str))
			return (0);
		j = 0;
		while (i < BUFFER_SIZE)
			(*buffer)[j++] = (*buffer)[i++];
		(*buffer)[j] = '\0';
	}
	return (1);
}

static char	*reading_loop(int fd, char (*buffer)[BUFFER_SIZE + 1], char **str)
{
	char	*temp;
	int		char_read;

	char_read = -1;
	while (ft_strchr(*str, '\n') == -1 && char_read != 0)
	{
		char_read = read(fd, (*buffer), BUFFER_SIZE);
		if (char_read == 0)
		{
			temp = cut_str(*str);
			(*buffer)[0] = '\0';
			return (temp);
		}
		if (char_read == -1)
			return (NULL);
		(*buffer)[char_read] = '\0';
		*str = ft_stradd(*str, (*buffer), char_read);
		if (!(*str))
			return (NULL);
	}
	temp = cut_str(*str);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char		buffer[BUFFER_SIZE + 1];
	char			*str;

	str = NULL;
	if (fd < 0 || read(fd, 0, 0) == -1 || BUFFER_SIZE <= 0)
	{
		buffer[0] = '\0';
		return (NULL);
	}
	if (buffer[0] != 0)
	{
		if (testing(&buffer, &str) == 0)
			return (NULL);
	}
	return (reading_loop(fd, &buffer, &str));
}
