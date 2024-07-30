CC = cc
FLAGS = -Wall -Wextra -Werror# -g -fsanitize=thread

NAME = philos

SRC_DIR = philo/src/
OBJ_DIR = philo/obj/
HEADER = $(addprefix $(SRC_DIR), philo.h)
FILES = init.c philo.c simulator.c utils.c routine.c
SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

BONUS = philosa
BONUS_SRC_DIR = philo_bonus/src/
BONUS_OBJ_DIR = philo_bonus/obj/
BONUS_HEADER = $(addprefix $(BONUS_SRC_DIR), philo_bonus.h)
BONUS_FILES = init_bonus.c philo_bonus.c simulator_bonus.c utils_bonus.c routine_bonus.c
BONUS_SRC = $(addprefix $(BONUS_SRC_DIR), $(BONUS_FILES))
BONUS_OBJ = $(addprefix $(BONUS_OBJ_DIR), $(BONUS_FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

bonus: $(BONUS)

$(BONUS): $(BONUS_OBJ_DIR) $(BONUS_OBJ)
	$(CC) $(FLAGS) -o $(BONUS) $(BONUS_OBJ)

$(BONUS_OBJ_DIR):
	mkdir -p $(BONUS_OBJ_DIR)

$(BONUS_OBJ_DIR)%.o: $(BONUS_SRC_DIR)%.c $(BONUS_HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BONUS_OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS)

re: fclean all

.PHONY: all clean fclean re