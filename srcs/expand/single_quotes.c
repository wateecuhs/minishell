/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 23:20:17 by waticouz          #+#    #+#             */
/*   Updated: 2024/01/12 11:22:35 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_single_quotes(char **src, size_t *i)
{
	char	*s;

	s = *src;
	s = ft_offset(s, *i);
	while (s[*i] && s[*i] != '\'')
		*i += 1;
	s = ft_offset(s, *i);
	*src = s;
	return (*i);
}
