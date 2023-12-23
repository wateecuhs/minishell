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

#endif