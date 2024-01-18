/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:26:31 by panger            #+#    #+#             */
/*   Updated: 2024/01/18 13:28:18 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*tab;
	unsigned int	i;
	unsigned int	b;

	b = 0;
	i = 0;
	if (!s)
		return (NULL);
	tab = (char *)malloc(sizeof(char) * (len + 1));
	if (!tab)
		return (perror_prefix("malloc"), NULL);
	while (s[i])
	{
		if (i >= start && b < len)
		{
			tab[b] = s[i];
			b++;
		}
		i++;
	}
	tab[b] = 0;
	return (tab);
}
