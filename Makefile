NAME				=	minishell

SRCS		=		minishell.c \
					dup_env.c \
					signal.c \
					signal2.c \
					$(SRCS_LIB) \
					$(SRCS_EXPAND) \
					$(SRCS_GNL) \
					$(SRCS_PARSING) \
					$(SRCS_EXEC) \
					$(SRCS_BUILTINS)

SRCS_EXPAND =		expand/expand.c \
					expand/single_quotes.c \
					expand/double_quotes.c \
					expand/no_quotes.c

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
					lib/ft_freetab.c \
					lib/ft_itoa.c \
					lib/free.c \
					lib/find_in_env.c

SRCS_EXEC	=		execution/get_data.c \
					execution/prepare_exec.c \
					execution/hub.c \
					execution/get_fd.c \
					execution/commands_handler.c\
					execution/errors.c \
					execution/paths.c \
					execution/heredoc.c \
					execution/heredoc_tools.c \
					execution/cmd_handling_tools.c

SRCS_BUILTINS=		builtins/cd.c \
					builtins/cd2.c \
					builtins/export.c \
					builtins/export2.c \
					builtins/env.c \
					builtins/pwd.c \
					builtins/echo.c \
					builtins/unset.c \
					builtins/exit.c \
					builtins/is_builtin.c

SRCS_PARSING=		parsing/first_parse.c \
					parsing/lexer.c \
					parsing/parsing.c

SRCS_GNL=			get_next_line/get_next_line.c \
					get_next_line/get_next_line_utils.c

SRC_PATH			=	srcs/
DIR_BUILD			=	.build/
OBJS				=	$(patsubst %.c, $(DIR_BUILD)%.o, $(SRCS))
OBJS_TEST			=	$(patsubst %.c, $(DIR_BUILD)%.o, $(TEST))
DEPS				=	$(patsubst %.c, $(DIR_BUILD)%.d, $(SRCS))
DEPS_FLAGS			=	-MMD -MP
BASE_CFLAGS			=	-g3 -Wall -Wextra -Werror
BASE_DEBUG_CFLAGS	=	-g3
DEBUG_CLFAGS		=	$(BASE_DEBUG_CFLAGS) -fsanitize=address
# DEBUG_CLFAGS		=	$(BASE_DEBUG_CFLAGS) -fsanitize=memory -fsanitize-memory-track-origins
# FLAGS				=	$(BASE_CFLAGS) -g3
# FLAGS				=	$(BASE_CFLAGS) -g3
# FLAGS				=	$(BASE_CFLAGS) $(BASE_DEBUG_CFLAGS)
FLAGS				=	$(BASE_CFLAGS)
# FLAGS				=	$(BASE_CFLAGS) $(DEBUG_CLFAGS)
# FLAGS				=	$(BASE_CFLAGS) $(DEBUG_CLFAGS)
RM					=	rm -rf
AR					=	ar rcs

DIR_INCS =\
	includes/

INCLUDES =\
	$(addprefix -I , $(DIR_INCS))


.PHONY:		all
all:
			$(MAKE) $(NAME)


$(NAME):	$(OBJS)
	$(CC) $(FLAGS) $(INCLUDES) $(OBJS) -o $(NAME) -lreadline

.PHONY:	clean
clean:
			$(RM) $(DIR_BUILD)
	
.PHONY:	fclean
fclean:	clean
			$(RM) $(NAME)

.PHONY:	debug
debug:	fclean
			$(MAKE) -j FLAGS="$(DEBUG_CLFAGS)"

.PHONY:	re
re:		fclean
			$(MAKE) all

-include $(DEPS)
$(DIR_BUILD)%.o : $(SRC_PATH)%.c
			@mkdir -p $(shell dirname $@)
			$(CC) $(FLAGS) $(DEPS_FLAGS) $(INCLUDES) -c $< -o $@