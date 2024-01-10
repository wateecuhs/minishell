/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 14:42:04 by waticouz          #+#    #+#             */
/*   Updated: 2024/01/10 17:15:15 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand_var(char	*s, size_t start, size_t stop, char *content)
{
	char	*ret;

	if (!content)
		content = ft_strdup("");
	printf("EXPANDING CONTENT %s\n", content);
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
	return (ret);
}
