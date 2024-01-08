/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcindrak <dcindrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:29:26 by dcindrak          #+#    #+#             */
/*   Updated: 2023/11/06 15:29:26 by dcindrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*mem;
	size_t	i;
	size_t	total;

	i = 0;
	total = count * size;
	mem = malloc(total);
	if (!mem)
		return (NULL);
	while (i < (count * size))
	{
		mem[i] = 0;
		i++;
	}
	return (mem);
}
