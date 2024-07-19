CC = cc
FLAGS = -Wall -Wextra -Werror
NAME = philo
SRC_DIR = src/
OBJ_DIR = obj/
HEADER = $(SRC_DIR)philo.h
FILES = philo.c init.c utils.c simulator.c routine.c
SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))


NAME = philo_bonus
SRC_DIR = bonus/src/
OBJ_DIR = bonus/obj/
HEADER = $(SRC_DIR)philo_bonus.h
FILES = philo_bonus.c init_bonus.c utils_bonus.c simulator_bonus.c routine_bonus.c
SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))


RED = \033[0;31m
GREEN = \033[0;32m
CYAN = \033[0;36m
BLUE = \033[0;34m
BOLD = \033[1m
RESET = \033[0m

all: $(OBJ_DIR) $(NAME)

$(LIBFT): $(LIBFT_DIR)
	@make -C $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	@echo "$(BLUE)$(BOLD)Creating executable...$(RESET)"
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)$(BOLD)$(NAME)Philo Created$(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "$(RED)$(BOLD)Object files removed$(RESET)"

fclean: clean
	@rm -f $(NAME) $(BONUS)
	@echo "$(RED)$(BOLD)$(NAME)Executable removed$(RESET)"

re: fclean all

.PHONY: all clean fclean re