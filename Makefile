CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror -IIncludes #-fsanitize=thread

NAME = philo

SRC = ${addprefix src/, main.c philo.c init.c routine.c monitor.c\
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

.PHONY: all clean fclean re
