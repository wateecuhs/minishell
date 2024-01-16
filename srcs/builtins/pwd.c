/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:45:12 by panger            #+#    #+#             */
/*   Updated: 2024/01/16 13:05:58 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(int fd[2])
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (!tmp)
	{
		perror("minishell");
		return (1);
	}
	write(fd[OUT], tmp, ft_strlen(tmp));
	write(fd[OUT], "\n", 1);
	free(tmp);
	return (0);
}
