/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waticouz <waticouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 23:20:17 by waticouz          #+#    #+#             */
/*   Updated: 2023/12/29 15:02:57 by waticouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_single_quotes(char **src, size_t *i)
{
	char	*s;

	s = *src;
	s = ft_offset(s, *i);
	*i += 1;
	while (s[*i] && s[*i] != '\'')
		*i += 1;
	s = ft_offset(s, *i);
	*src = s;
	return (*i);
}
