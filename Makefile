RED = \033[0;31m
GREEN = \033[0;32m
CYAN = \033[0;36m
BLUE = \033[0;34m
BOLD = \033[1m
RESET = \033[0m

CC=CC
FLAGS=-Wall -Werror -Wextra -g -fsanitize=address#-lpthread

NAME=philos
SRC_FOLDER=philo/src/
OBJ_FOLDER=philo/obj/
HEADER=$(SRC_FOLDER)/../philo.h
FILES= philo.c utils.c init.c simulator.c routine.c
SRC=$(addprefix $(SRC_FOLDER), $(FILES))
OBJ=$(addprefix $(OBJ_FOLDER), $(FILES:.c=.o))	

all: $(OBJ_FOLDER) $(NAME)

$(OBJ_FOLDER):
	@mkdir -p $(OBJ_FOLDER)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ)


$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.c $(HEADER)
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_FOLDER)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re