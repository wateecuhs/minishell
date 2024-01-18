/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:24:44 by panger            #+#    #+#             */
/*   Updated: 2024/01/18 13:27:40 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_len(long int nb)
{
	int	len;

	len = 1;
	if (nb < 0)
	{
		len++;
		nb = -nb;
	}
	while (nb > 9)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int			i;
	long int	nb;
	char		*str;
	int			len;

	len = find_len((long int)n);
	nb = (long int)n;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (perror_prefix("malloc"), NULL);
	str[len] = '\0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	i = 1;
	while (nb > 9)
	{
		str[len - i] = (nb % 10) + 48;
		nb /= 10;
		i++;
	}
	str[len - i] = (nb % 10) + 48;
	return (str);
}
