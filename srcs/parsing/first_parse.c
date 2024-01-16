/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:27:17 by panger            #+#    #+#             */
/*   Updated: 2024/01/16 13:33:26 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_unclosed(char *str)
{
	int	quote;

	quote = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			if (quote == 0)
				quote = *str;
			else if (quote == *str)
				quote = 0;
		}
		str++;
	}
	if (quote != 0)
	{
		printf("Error: quote not closed\n");
		return (1);
	}
	return (0);
}

static int	nothing_after_pipe(char *str, int i)
{
	int	before;

	before = i;
	while (before >= 0 && str[before] != '|')
		before--;
	before--;
	while (before >= 0 && (str[before] == ' ' || str[before] == '\t'
			|| str[before] == '\n'))
		before--;
	if (before <= 0 || str[before] == '|')
		return (1);
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

int	sub_error(char curr, char next)
{
	if (curr == '<')
	{
		if (next == '<')
			return (printf("parse error near '<<'\n"), 1);
		else
			return (printf("parse error near '<'\n"), 1);
	}
	else if (curr == '>')
	{
		if (next == '>')
			return (printf("parse error near '>>'\n"), 1);
		else
			return (printf("parse error near '>'\n"), 1);
	}
	return (0);
}

static int	find_error(char *str, int i, int initial)
{
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	if (str[i] == '|' || str[initial - 1] == '|')
	{
		if (nothing_after_pipe(str, i) == 1 || str[initial - 1] == '>'
			|| str[initial - 1] == '<')
			return (printf("parse error near '|'\n"), 1);
		return (0);
	}
	else if (sub_error(str[i], str[i + 1]) == 1)
		return (1);
	if (str[i] == '\0')
		return (printf("parse error near '\\n'\n"), 1);
	return (0);
}

int	check_if_broken_enum(char *str)
{
	int	i;
	int	pos;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			pos = i++;
			while (str[i] != str[pos])
				i++;
		}
		else if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		{
			if ((str[i + 1] == '<' || str[i + 1] == '>') && str[i
					+ 1] == str[i])
				i++;
			if (find_error(str, i + 1, i + 1) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}
