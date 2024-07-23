RED = \033[0;31m
GREEN = \033[0;32m
CYAN = \033[0;36m
BLUE = \033[0;34m
BOLD = \033[1m
RESET = \033[0m

CC=CC
FLAGS=-Wall -Werror -Wextra -g -fsanitize=thread

NAME=philo/philo
SRC_FOLDER=philo/src/
OBJ_FOLDER=philo/obj/
HEADER=$(SRC_FOLDER)/../philo.h
FILES= philo.c utils.c init.c simulator.c routine.c
SRC=$(addprefix $(SRC_FOLDER), $(FILES))
OBJ=$(addprefix $(OBJ_FOLDER), $(FILES:.c=.o))

BONUS_NAME=philo_bonus/philo_bonus
BONUS_SRC_FOLDER=philo_bonus/src/
BONUS_OBJ_FOLDER=philo_bonus/obj/
BONUS_HEADER=$(SRC_FOLDER)/../philo_bonus.h
BONUS_FILES= philo_bonus.c utils_bonus.c init_bonus.c simulator_bonus.c routine_bonus.c
BONUS_SRC=$(addprefix $(SRC_FOLDER), $(FILES))
BONUS_OBJ=$(addprefix $(OBJ_FOLDER), $(FILES:.c=.o))	

all: $(OBJ_FOLDER) $(NAME) $(BONUS_NAME)

$(BONUS_OBJ_FOLDER):
	@mkdir -p $(BONUS_OBJ_FOLDER)

$(BONUS_NAME): $(BONUS_OBJ)
	@echo "$(CYAN)Compiling...$(RESET)"
	@$(CC) $(FLAGS) -o $(BONUS_NAME) $(BONUS_OBJ)
	@echo "$(GREEN)$(BOLD)$(BONUS_NAME)$(RESET) $(GREEN)compiled successfully!$(RESET)"

$(OBJ_FOLDER):
	@mkdir -p $(OBJ_FOLDER)

$(NAME): $(OBJ)
	@echo "$(CYAN)Compiling...$(RESET)"
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ)
	@echo "$(GREEN)$(BOLD)$(NAME)$(RESET) $(GREEN)compiled successfully!$(RESET)"


$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.c $(HEADER)
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_FOLDER) $(BONUS_OBJ_FOLDER)

fclean: clean
	@rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re