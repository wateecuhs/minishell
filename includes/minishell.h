#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef enum {
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
} TokenType;

typedef struct s_token{
    TokenType type;
    char *value;
    struct s_token *next;
} t_token;

int		is_whitespace(char c);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		ft_strlen(char *s);
int		expand_single_quotes(char *s, int *i);
char	*ft_strjoin_free(char *s1, char *s2, size_t size);

#endif