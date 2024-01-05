/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 15:55:28 by waticouz          #+#    #+#             */
/*   Updated: 2024/01/05 16:47:41 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdarg.h>
# include <string.h>

# define IN 1
# define OUT 0
# define READ 0
# define WRITE 1

typedef enum tokenTypes
{
	WORD,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	HEREDOC,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	ENV_VARIABLE,
	EXIT_STATUS,
	AND,
	OR,
	// Add more token types as needed
}	t_tokenType;

typedef struct s_token
{
	t_tokenType		type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

int		is_whitespace(char c);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		ft_tablen(char **s);
int		ft_strlen(char *s);
int		expand_single_quotes(char **src, size_t *i);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_strns1join(char *s1, char *s2, size_t size);
char	*ft_strns2join(char *s1, char *s2, size_t size);
char	*ft_strndup(char *s, int size);
char	*ft_expand_var(char	*s, size_t start, size_t stop, char *content);
int		ft_isalnum(int c);
int		ft_isdigit(int c);
char	*ft_strdup(char *s);
int		is_valid_char(int c);
int		ft_strchr(const char *s, int c);
int		ft_strnchr_dollar(const char *s, int len);
char	*ft_offset(char *s, int i);
int		expand_double_quotes(char **src, size_t *i, char **env);
int		get_var_name(char *s, size_t i);
char	*parse_env(char **env, char *to_find);

char	*get_next_line(int fd);
int		ft_strlen(char *str);
char	*ft_strdupset(char const *s, int start, int stop);
char	*ft_stradd(char *s1, char *s2, int size);

#endif