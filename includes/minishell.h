/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 15:55:28 by waticouz          #+#    #+#             */
/*   Updated: 2024/01/09 13:54:12 by panger           ###   ########.fr       */
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
# include <sys/ioctl.h>
# include <stdarg.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# define IN 1
# define OUT 0
# define READ 0
# define WRITE 1
# define READ_END 0
# define WRITE_END 1
# define EXEC_ERROR 126
# define NOT_FOUND 127
# define FATAL 128
# define USAGE_ERROR 258

typedef enum {
    WORD,
    PIPE,
    REDIRECT_IN,
    REDIRECT_OUT,
    REDIRECT_APPEND,
    HEREDOC,
    EXIT_STATUS,
} TokenType;


typedef struct s_token
{
	TokenType		type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_redirs
{
	TokenType		type;
	char			*value;
	struct s_redirs	*next;
}	t_redirs;

typedef struct s_block
{
	char			*cmd;
	char			**args;
	t_redirs		*redirs;
	struct s_block	*next;
	int				pid;
}	t_block;

//lib
int		is_whitespace(char c);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		ft_tablen(char **s);
size_t	ft_strlen(char *str);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_strns1join(char *s1, char *s2, size_t size);
char	*ft_strns2join(char *s1, char *s2, size_t size);
char	*ft_strndup(char *s, int size);
int		ft_isalnum(int c);
int		ft_isdigit(int c);
char	*ft_strdup(char *s);
int		is_valid_char(int c);
int		ft_strchr(const char *s, int c);
int		ft_strnchr_dollar(const char *s, int len);
char	*ft_expand_var(char	*s, size_t start, size_t stop, char *content);
char	*ft_offset(char *s, int i);
void 	lst_free(t_token *lst);
t_token *lst_new(TokenType type, char *value);
int 	ft_lstadd_back(t_token **alst, t_token *new);
t_token	*ft_lstlast(t_token *lst);
int 	ft_strcmp(const char *s1, const char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t count, size_t size);
void	lst_addback_blocks(t_block **lst, t_block *new);
void	lst_addback_redirs(t_redirs **lst, t_redirs *new);
void	print_lst(t_token *lst);
void 	free_tokens(t_token *tokens);
int		command_receiver(t_block *blocks, char **env, int heredoc);
int		get_fd(int fd[4], t_block *block, int i);
char	**ft_split_s(char *s, char *c);
void	freetab(char **tab);

int		expand(t_token *head, char **env);
int		expand_double_quotes(char **src, size_t *i, char **env);
int		get_var_name(char *s, size_t i);
char	*parse_env(char **env, char *to_find);
int		expand_single_quotes(char **src, size_t *i);
int		count_blocks(t_token *tokens);
int		count_words_in_block(t_token *tokens);
t_block	*words_to_blocks(t_token *tokens);
int		execution_hub(t_token *tokens, char **env);
char	*get_cmd(t_token *token);
char	**get_args(t_token *token);
t_redirs	*assign_redir(t_token *token);
t_redirs	*get_redirs(t_token *token);
int			parsing(char *input, t_token *tokens);
int		get_fd(int fd[4], t_block *block, int i);
int		*set_fd_to_use(int *fd, int fd_in, int fd_out);
char	*find_path(char *cmd, char **env);
void	error_msg(char *string);
char	*ft_strjoin(char *s1, char *s2);

//gnl
char	*get_next_line(int fd);
char	*ft_strdupset(char const *s, int start, int stop);
char	*ft_stradd(char *s1, char *s2, int size);

//lexer - parse
int tokenize(t_token **token , char *input);
int	get_token_type(char *tokenValue);
int check_unclosed(char *str);
int check_if_broken_enum(char *str);

#endif