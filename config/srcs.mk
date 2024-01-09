SRCS		=		minishell.c \
					$(SRCS_LIB) \
					$(SRCS_EXPAND) \
					$(SRCS_GNL) \
					$(SRCS_PARSING) \
					$(SRCS_EXEC)

SRCS_EXPAND =		expand/expand.c \
					expand/single_quotes.c \
					expand/double_quotes.c

SRCS_LIB	=		lib/ft_expand_var.c \
					lib/ft_isalnum.c \
					lib/ft_isdigit.c \
					lib/ft_strdup.c \
					lib/ft_strjoin.c \
					lib/ft_strlen.c \
					lib/ft_strncmp.c \
					lib/is_alpha.c \
					lib/is_valid_char.c \
					lib/is_whitespace.c \
					lib/ft_strchr.c \
					lib/ft_offset.c \
					lib/lst.c \
					lib/ft_substr.c \
					lib/ft_split.c \
					lib/ft_calloc.c \
					lib/lst_addback_blocks.c \
					lib/ft_split_s.c \
					lib/ft_freetab.c

SRCS_EXEC	=		execution/get_data.c \
					execution/prepare_exec.c \
					execution/hub.c \
					execution/get_fd.c \
					execution/commands_handler.c\
					execution/errors.c \
					execution/paths.c

SRCS_PARSING=		parsing/first_parse.c \
					parsing/lexer.c \
					parsing/parsing.c

SRCS_GNL=			get_next_line/get_next_line.c \
					get_next_line/get_next_line_utils.c