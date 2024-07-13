CC = cc
FLAGS = -Wall -Wextra -Werror -g -fsanitize=thread

NAME = philo
SRC_DIR = src/
OBJ_DIR = obj/
HEADER = $(SRC_DIR)philo.h
FILES = philo.c init.c utils.c simulator.c routine.c
SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

# BONUS = minishell_bonus
# BONUS_SRC_DIR = bonus/src/
# BONUS_OBJ_DIR = bonus/obj/
# BONUS_HEADER = $(BONUS_SRC_DIR)minishell_bonus.h
# BONUS_FILES = 
# BONUS_SRC = $(addprefix $(BONUS_SRC_DIR), $(BONUS_FILES))
# BONUS_OBJ = $(addprefix $(BONUS_OBJ_DIR), $(BONUS_FILES:.c=.o))

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
	@echo "$(CYAN)$(BOLD)Compiling... $<$(RESET)"
	@$(CC) $(FLAGS) -c $< -o $@

# bonus: $(LIBFT) $(BONUS_OBJ_DIR) $(BONUS)

# $(BONUS_OBJ_DIR):
# 	mkdir -p $(BONUS_OBJ_DIR)

# $(BONUS): $(BONUS_OBJ)
# 	@echo "$(BLUE)$(BOLD)Creating $(BONUS) executable...$(RESET)"
# 	$(CC) $(FLAGS) $(BONUS_OBJ) $(LIBFT) $(GNL) -o $(BONUS)
# 	@echo "$(GREEN)$(BOLD)$(BONUS) created$(RESET)"

# $(BONUS_OBJ_DIR)%.o: $(BONUS_SRC_DIR)%.c $(BONUS_HEADER) $(GNL_HEADER)
# 	@echo "$(CYAN)$(BOLD)Compiling $<$(RESET)"
# 	$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "$(RED)$(BOLD)Object files removed$(RESET)"

fclean: clean
	@rm -f $(NAME) $(BONUS)
	@echo "$(RED)$(BOLD)$(NAME)Executable removed$(RESET)"

re: fclean all

.PHONY: all clean fclean re