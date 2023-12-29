/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waticouz <waticouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:46:38 by waticouz          #+#    #+#             */
/*   Updated: 2023/12/26 19:02:56 by waticouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void	func(char **test)
{
	int	i;
	char *tmp;

	i = 0;
	tmp = *test;
	while (tmp[i] && tmp[i + 1])
	{
		tmp[i] = tmp[i + 1];
		i++;
	}
	tmp[i] = '\0';
	*test = tmp;
}

int	main(void)
{
	char *test;

	test = (char *)malloc(sizeof(char) * 10);
	test = strcpy(test, "test12345");
	printf("%s\n", test);
	func(&test);
	printf("%s\n", test);
}