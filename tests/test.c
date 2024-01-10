/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:46:38 by waticouz          #+#    #+#             */
/*   Updated: 2024/01/10 15:36:44 by panger           ###   ########.fr       */
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

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (strdup(s2));
	if (!s2)
		return (strdup(s1));
	str = (char *)malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
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
	env[i] = ft_strjoin("OLDPWD", &env[j][3]);
	chdir("..");
	env[j] = ft_strjoin("PWD=", getcwd(NULL, 0));
}