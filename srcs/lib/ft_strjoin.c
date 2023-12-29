/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waticouz <waticouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 23:24:09 by waticouz          #+#    #+#             */
/*   Updated: 2023/12/29 15:59:05 by waticouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strns1join(char *s1, char *s2, size_t size)
{
	size_t		i;
	size_t		j;
	char		*str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	str = (char *)malloc(sizeof(char) * (ft_strlen(s2) + size + 1));
	if (!str)
		return (free(s1), NULL);
	i = 0;
	while (s1[i] && i < size)
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

char	*ft_strns2join(char *s1, char *s2, size_t size)
{
	size_t		i;
	size_t		j;
	char		*str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + size + 1));
	if (!str)
		return (free(s1), NULL);
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
	return (str);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	size_t		i;
	size_t		j;
	char		*str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (free(s1), NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}
