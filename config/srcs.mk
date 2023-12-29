SRCS		=		$(SRCS_LIB) \
					$(SRCS_EXPAND)

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
					lib/ft_offset.c