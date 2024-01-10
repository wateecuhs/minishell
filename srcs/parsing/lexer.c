/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:27:09 by panger            #+#    #+#             */
/*   Updated: 2024/01/10 17:37:26 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_token_type(char *tokenValue)
{
	if (ft_strcmp(tokenValue, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(tokenValue, "<") == 0)
		return (REDIRECT_IN);
	else if (ft_strcmp(tokenValue, ">") == 0)
		return (REDIRECT_OUT);
	else if (ft_strcmp(tokenValue, ">>") == 0)
		return (REDIRECT_APPEND);
	else if (ft_strcmp(tokenValue, "<<") == 0)
		return (HEREDOC);
	else
		return (WORD);
}

int	len_to_quote(char *str)
{
	int	i;
	int	pos;
	int	compt;

	i = 0;
	pos = 0;
	compt = 0;
	while (str[i])
	{
		if (str[pos] == str[i] && compt < 2)
			compt++;
		if (compt == 2 && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
				|| str[i] == '>' || str[i] == '<' || str[i] == '|'))
			return (i);
		else if (compt == 2)
		{
			pos = i + 1; //check
			if (str[i + 1] == '\"' || str[i + 1] == '\'')
				compt = 0;
		}
		i++;
	}
	return (i + 1);
}

int	len_to_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
	{
		if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		{
			if (i != 0)
				return (i);
			if (str[i + 1] == str[i])
				return (i + 2);
			if (str[i + 1] != str[i])
				return (i + 1);
		}
		i++;
		if (str[i] == '\'' || str[i] == '\"')
		{
			i += len_to_quote(str + i) - 1;
		}
	}
	return (i);
}

int	tokenize(t_token **token, char *input)
{
	char	*tokenValue;
	int		i;

	i = -1;
	while (input[++i])
	{
		if (input[i] != ' ' && input[i] != '\t' && input[i] != '\n')
		{
			if (input[i] == '\'' || input[i] == '\"')
			{
				if (len_to_quote(input + i) == -1)
					return (1);
				tokenValue = ft_substr(input, i, len_to_quote(input + i));
			}
			else
				tokenValue = ft_substr(input, i, len_to_space(input + i));
			if (tokenValue == NULL)
				return (1);
			if (ft_lstadd_back(token, lst_new(get_token_type(tokenValue),
						tokenValue)) == 1)
				return (1);
			i += ft_strlen(tokenValue) - 1;
		}
	}
	return (0);
}
