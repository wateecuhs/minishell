/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waticouz <waticouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:08:28 by panger            #+#    #+#             */
/*   Updated: 2023/12/29 16:17:09 by waticouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	if (s == NULL)
		return (-1);
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return (i);
		i++;
	}
	if (s[i] == (unsigned char)c)
		return (i);
	return (-1);
}

int	ft_strnchr_dollar(const char *s, int len)
{
	unsigned int	i;

	i = 0;
	if (len <= -1)
		return (-1);
	while (s[i] && i < (unsigned int)len)
	{
		if (s[i] == '$' && is_valid_char(s[i + 1] == 1))
			return (i);
		i++;
	}
	return (-1);
}
