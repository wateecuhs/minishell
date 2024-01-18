/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:02:44 by panger            #+#    #+#             */
/*   Updated: 2024/01/18 18:12:43 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdupset(char const *s, int start, int stop)
{
	char			*trg;
	unsigned int	count;
	int				i;

	i = 0;
	count = 0;
	while (s[count])
		count++;
	trg = (char *)malloc((stop - start + 1) * sizeof(char));
	if (!trg)
		return (perror_prefix("malloc"), NULL);
	while (s[start] && start < stop)
	{
		trg[i] = s[start];
		i++;
		start++;
	}
	trg[i] = '\0';
	return (trg);
}

char	*ft_stradd(char *s1, char *s2, int size)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + size + 1));
	if (!str)
		return (perror_prefix("malloc"), NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] && j < size)
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}
