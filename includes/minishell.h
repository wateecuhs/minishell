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

#endif