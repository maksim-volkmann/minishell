CC = cc
# CFLAGS = -Wall -Wextra -Werror
CFLAGS=-fsanitize=address
LIBS = -lreadline

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
MAGENTA = \033[1;35m
CYAN = \033[1;36m
RESET = \033[0m

NAME = minishell
LIBFT_NAME = libft.a

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes
LIBFT_DIR = libft/src

SRC = $(shell find $(SRC_DIR) -type f -name "*.c")
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

LIBFT_SRC_DIR = $(LIBFT_DIR)
LIBFT_OBJ_DIR = $(LIBFT_DIR)/obj
LIBFT_SRC = $(wildcard $(LIBFT_SRC_DIR)/*.c)
LIBFT_OBJ = $(LIBFT_SRC:$(LIBFT_SRC_DIR)/%.c=$(LIBFT_OBJ_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@echo "$(CYAN)Starting compilation process for $<...$(RESET)"
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@
	@echo "$(BLUE)Compiled $< to $@.$(RESET)"
	@echo "$(CYAN)Compilation process for $< finished.$(RESET)"

$(NAME): $(OBJ) $(LIBFT_OBJ)
	@echo "$(CYAN)Starting linking process...$(RESET)"
	@echo "$(YELLOW)Linking object files...$(RESET)"
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_OBJ) $(LIBS) -o $@
	@echo "$(GREEN)Linking done. Executable created: $(NAME)$(RESET)"
	@echo "$(CYAN)Linking process finished.$(RESET)"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT_OBJ_DIR)/%.o: $(LIBFT_SRC_DIR)/%.c | $(LIBFT_OBJ_DIR)
	@echo "$(CYAN)Starting compilation process for $<...$(RESET)"
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(LIBFT_DIR)/includes -c $< -o $@
	@echo "$(BLUE)Compiled $< to $@.$(RESET)"
	@echo "$(CYAN)Compilation process for $< finished.$(RESET)"

$(LIBFT_OBJ_DIR):
	mkdir -p $(LIBFT_OBJ_DIR)

clean:
	@echo "$(CYAN)Starting cleaning process...$(RESET)"
	@echo "$(MAGENTA)Cleaning object files...$(RESET)"
	rm -rf $(OBJ_DIR)
	rm -f $(NAME)
	make -C $(LIBFT_DIR) clean
	@echo "$(RED)Cleaning done.$(RESET)"
	@echo "$(CYAN)Cleaning process finished.$(RESET)"

fclean: clean
	@echo "$(CYAN)Starting full cleaning process...$(RESET)"
	@echo "$(MAGENTA)Full cleaning...$(RESET)"
	make -C $(LIBFT_DIR) fclean
	@echo "$(RED)Full cleaning done. Removed executable: $(NAME)$(RESET)"
	@echo "$(CYAN)Full cleaning process finished.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
