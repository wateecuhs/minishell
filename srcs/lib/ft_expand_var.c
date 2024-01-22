/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 14:42:04 by waticouz          #+#    #+#             */
/*   Updated: 2024/01/22 16:04:19 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand_var(char	*s, size_t start, size_t stop, char *content)
{
	char	*ret;
	int		free_content;

	free_content = 0;
	if (!content)
	{
		free_content = 1;
		content = ft_strdup("");
	}
	if (!content)
		return (free(s), NULL);
	ret = ft_strndup(s, start);
	if (!ret)
		return (free(s), free(content), NULL);
	ret = ft_strjoin_free(ret, content);
	if (!ret)
		return (free(s), free(content), NULL);
	ret = ft_strjoin_free(ret, &s[stop + 1]);
	if (!ret)
		return (free(s), free(content), NULL);
	free(s);
	if (free_content == 1)
		free(content);
	return (ret);
}
