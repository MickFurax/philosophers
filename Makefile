################################################################################
#                                     CONFIG                                   #
################################################################################

NAME        := philosopher
CC          := cc
FLAGS       := -Wall -Wextra -Werror
TEST_FLAGS  := -fsanitize=thread

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS        :=      srcs/ft_utils/ft_philo.c \
                          srcs/ft_utils/ft_action.c \
                          srcs/ft_utils/ft_data.c \
                          srcs/ft_utils/ft_fork.c \
                          srcs/main.c \
                          
OBJS        := $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

################################################################################
#                                  Makefile  objs                              #
################################################################################

CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f

${NAME}:	${OBJS}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			${CC} ${FLAGS} -o ${NAME} ${OBJS}
			@echo "$(GREEN)$(NAME) created$(CLR_RMV) ✔️"

all:		${NAME} test

test:       clean
			@echo "$(GREEN)Compilation for testing with ${TEST_FLAGS} $(CLR_RMV)..."
			${CC} ${FLAGS} ${TEST_FLAGS} -o ${NAME}_test ${SRCS}
			@echo "$(GREEN)${NAME}_test created$(CLR_RMV) ✔️"

bonus:		all

clean:
			@ ${RM} *.o */*.o */*/*.o ${NAME}_test
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:		clean
			@ ${RM} ${NAME}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re:			fclean all

.PHONY:		all clean fclean re test
