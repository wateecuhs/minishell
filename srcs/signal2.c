/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:32:19 by panger            #+#    #+#             */
/*   Updated: 2024/01/18 12:35:14 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child(int sig)
{
	(void)sig;
	if (g_status_code == 2)
	{
		g_status_code = 130;
		write(1, "\n", 1);
	}
	if (g_status_code == 131)
		write(1, "Quit (core dumped)\n", 19);
}
