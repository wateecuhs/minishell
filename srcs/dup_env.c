/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:43:52 by panger            #+#    #+#             */
/*   Updated: 2024/01/16 13:15:21 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dup_env(char ***env)
{
	char	**tmp;
	int		len;
	int		i;

	len = ft_tablen(*env);
	tmp = (char **)malloc(sizeof(char *) * (len + 1));
	if (!tmp)
		return (-1);
	i = 0;
	while ((*env)[i])
	{
		tmp[i] = ft_strdup((*env)[i]);
		if (!(tmp[i]))
			return (freetabn(tmp, i - 1), -1);
		i++;
	}
	tmp[i] = NULL;
	*env = tmp;
	return (0);
}
