/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:26:33 by panger            #+#    #+#             */
/*   Updated: 2024/01/09 13:50:26 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_tab(char **tab, int k)
{
	int	i;

	i = 0;
	while (i < k)
		free(tab[i++]);
	free(tab);
}

static unsigned int	in_charset(char c, char *charset)
{
	int	j;

	j = 0;
	while (charset[j])
	{
		if (charset[j] == c)
		{
			return (1);
		}
		j++;
	}
	return (0);
}

unsigned int	next_charset(char *str, char *charset, int i)
{
	int	j;
	int	k;

	k = i;
	while (str[k])
	{
		j = 0;
		while (charset[j])
		{
			if (str[k] == charset[j])
				return (k);
			j++;
		}
		k++;
	}
	return (k);
}

static unsigned int	count_words(char *s, char *c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((in_charset(s[i + 1], c) == 1 || s[i + 1] == '\0')
			&& in_charset(s[i], c) == 0)
			count++;
		i++;
	}
	return (count);
}

char	**ft_split_s(char *s, char *c)
{
	char			**tab;
	unsigned int	i;
	unsigned int	k;

	i = 0;
	k = 0;
	if (!s)
		return (NULL);
	tab = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	while (s[i])
	{
		if (in_charset(s[i], c) == 0)
		{
			tab[k++] = ft_substr(s, i, next_charset(s, c, i) - i);
			if (!tab[k - 1])
				return (free_tab(tab, k - 1), NULL);
			i = next_charset(s, c, i);
		}
		if (s[i])
			i++;
	}
	tab[k] = 0;
	return (tab);
}
