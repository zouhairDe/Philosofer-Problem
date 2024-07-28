CC = cc
FLAGS = -Wall -Wextra -Werror# -g -fsanitize=address

NAME = philos

SRC_DIR = philo/src/
OBJ_DIR = philo/obj/
HEADER = $(addprefix $(SRC_DIR), philo.h)
FILES = init.c philo.c simulator.c utils.c routine.c
SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f philo/$(NAME)

re: fclean all

.PHONY: all clean fclean re