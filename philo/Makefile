NAME = philo
CC = cc
FLAGS = -Wall -Wextra -Werror
THREADSANITIZER = -fsanitize=thread

SRCS = srcs/main.c srcs/utils/data.c srcs/utils/philo.c srcs/utils/time.c
OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

threadsanitizer: $(OBJS)
	$(CC) $(FLAGS) $(THREADSANITIZER) -o ${NAME}_threadsanitizer $(OBJS)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o ${NAME} $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME)_threadsanitizer

re: fclean all

.PHONY: all clean fclean re

