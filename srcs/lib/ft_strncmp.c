/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 22:43:12 by waticouz          #+#    #+#             */
/*   Updated: 2024/01/15 11:31:59 by panger           ###   ########.fr       */
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

int ft_strcmp(const char *s1, const char *s2)
{
    int i;

	if (s1 == NULL || s2 == NULL)
        return (-1);
	i = 0;
	while (s1[i] && s2[i] == s1[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_strcmp_hd(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (-1);
	while (s1[i] && s1[i] == s2[i])
		i++;
	if (s1[i] == '\n' && s1[i +1] == '\0' && s2[i] == '\0')
		return (0);
	return (s1[i] - s2[i]);
}