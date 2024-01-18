/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:18:44 by panger            #+#    #+#             */
/*   Updated: 2024/01/18 12:31:23 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	remove_quotes(char **src, size_t *i, char quote_type)
{
	char	*s;

	s = *src;
	s = ft_offset(s, *i);
	while (s[*i] && s[*i] != quote_type)
		*i += 1;
	s = ft_offset(s, *i);
	*i = *i - 1;
	*src = s;
	return (*i);
}

char	*expand_limiter(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			remove_quotes(&s, &i, s[i]);
		i++;
	}
	return (s);
}
