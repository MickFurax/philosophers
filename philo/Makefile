NAME = philo
CC = cc
FLAGS = -Wall -Wextra -Werror

SRCS = srcs/main.c srcs/utils/data.c srcs/utils/philo.c \
		srcs/utils/time.c srcs/utils/action.c srcs/utils/utils.c \
		srcs/utils/priority.c srcs/utils/dead.c

OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o ${NAME} $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

