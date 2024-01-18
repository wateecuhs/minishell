/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcindrak <dcindrak@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 23:25:02 by waticouz          #+#    #+#             */
/*   Updated: 2024/01/18 14:57:31 by dcindrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *s)
{
	size_t	srclen;
	size_t	i;
	char	*dest;

	srclen = 0;
	if (!s)
		return (NULL);
	while (s[srclen])
		srclen++;
	i = 0;
	dest = (char *)malloc((srclen + 1) * sizeof(char));
	if (!dest)
		return (perror_prefix("malloc"), NULL);
	while (i < srclen)
	{
		dest[i] = s[i];
		i ++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strndup(char *s, int size)
{
	size_t	i;
	char	*dest;

	i = 0;
	dest = (char *)malloc((size + 1) * sizeof(char));
	if (!dest)
		return (perror_prefix("malloc"), NULL);
	while (i < (size_t)size)
	{
		dest[i] = s[i];
		i ++;
	}
	dest[i] = '\0';
	return (dest);
}
