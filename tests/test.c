/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:46:38 by waticouz          #+#    #+#             */
/*   Updated: 2024/01/09 15:30:17 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i] && (i < n))
	{
		i ++;
	}
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	main(int argc, char **argv, char **env)
{
	char	*tmp;
	int	i;
	int	j;

	i = 0;
	while (ft_strncmp(env[i], "OLDPWD=", 7) != 0)
		i++;
	j = 0;
	while (ft_strncmp(env[j], "PWD=", 4) != 0)
		j++;
	env[i] = strdup(env[j]);
	chdir("..");
	env[j] = getcwd(NULL, 0);
	printf("%s\n", env[i]);
}