NAME				=	minishell

include config/srcs.mk
SRC_PATH			=	srcs/
DIR_BUILD			=	.build/
OBJS				=	$(patsubst %.c, $(DIR_BUILD)%.o, $(SRCS))
OBJS_TEST			=	$(patsubst %.c, $(DIR_BUILD)%.o, $(TEST))
DEPS				=	$(patsubst %.c, $(DIR_BUILD)%.d, $(SRCS))
DEPS_FLAGS			=	-MMD -MP
BASE_CFLAGS			=	-g3 -Wall -Wextra #-Werror
BASE_DEBUG_CFLAGS	=	-g3
DEBUG_CLFAGS		=	$(BASE_DEBUG_CFLAGS) -pthread -fsanitize=address
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
	$(CC) $(FLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

.PHONY:	clean
clean:
			$(RM) $(DIR_BUILD)
	
.PHONY:	fclean
fclean:	clean
			$(RM) $(NAME)

.PHONY:	debug
debug:
			$(MAKE) -j FLAGS="$(DEBUG_CLFAGS)"

.PHONY:	re
re:		fclean
			$(MAKE) all

-include $(DEPS)
$(DIR_BUILD)%.o : $(SRC_PATH)%.c
			@mkdir -p $(shell dirname $@)
			$(CC) $(FLAGS) $(DEPS_FLAGS) $(INCLUDES) -c $< -o $@
