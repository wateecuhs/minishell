/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waticouz <waticouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 22:43:12 by waticouz          #+#    #+#             */
/*   Updated: 2023/12/22 22:49:22 by waticouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i] && (i < n))
	{
		i ++;
	}
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
