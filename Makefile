CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror -IIncludes

NAME = philo

SRC = ${addprefix src/, main.c manage_philos_life.c init.c routine.c monitor.c\
	${addprefix aux/, utils.c ft_functions.c clean.c}}

OBJ = $(SRC:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "."

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)
	@printf "all clean"

re: fclean all

run: philo
	TSAN_OPTIONS=second_deadlock_stack=1 ./philo 4 410 200 200 7

.PHONY: all clean fclean re
