CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror -IIncludes

NAME = philo

SRC_DIR = src/
OBJ_DIR = build/

SRC = ${addprefix $(SRC_DIR), main.c manage_philos_life.c init.c routine.c monitor.c\
	${addprefix aux/, utils.c ft_functions.c clean.c}}

OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c Includes/philo.h
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "."

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)
	@printf "all clean\n"

re: fclean all

tsan: fclean
	@$(MAKE) all CFLAGS="$(CFLAGS) -fsanitize=thread"
	@TSAN_OPTIONS=second_deadlock_stack=1 ./$(NAME) 4 410 200 200 10

.PHONY: all clean fclean re tsan
