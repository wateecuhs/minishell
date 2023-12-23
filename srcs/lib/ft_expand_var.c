/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waticouz <waticouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 14:42:04 by waticouz          #+#    #+#             */
/*   Updated: 2023/12/23 16:35:43 by waticouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand_var(char	*s, size_t start, size_t stop, char *content)
{
	size_t	i;
	size_t	j;
	int		len;
	char	*ret;

	len = ft_strlen(s) - (stop - start) + ft_strlen(content);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	while (s[i] && i < start)
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	ret = ft_strjoin_free(ret, content);
	i = ft_strlen(ret);
	j = stop + 1;
	while (j < (size_t)ft_strlen(s) && s[j])
		ret[i++] = s[j++];
	ret[i] = '\0';
	return (ret);
}
