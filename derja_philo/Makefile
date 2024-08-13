NAME		     =	philo
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror #-g3 -fsanitize=thread
RM			=	rm -rf	
SRC			=	philo.c \
				utils/ft_strlen.c utils/ft_atoi.c \
				utils/ft_error.c utils/init.c utils/print_action.c utils/check_if_philo_died.c \
				utils/philosopher_rutine.c utils/clean_threads.c utils/philo_threads.c \
				utils/timestamp.c \
				
OBJ			=	$(SRC:.c=.o)
HEADER		= includes/

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -I$(HEADER) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MLX_FLAGS)


clean:
	$(RM) $(OBJ)
	
fclean: clean
	$(RM) $(NAME)
	
re: fclean all
	
.PHONY: all clean fclean re
