# Compiler and flags
CC = cc
# CFLAGS = -Wall -Wextra -Werror
# CFLAGS = -fsanitize=address -g

# Project name
NAME = minishell

# Directories
SRC_DIR = src
OBJ_DIR = obj
LIBFT_DIR = libft
INC_DIR = includes

# Library
LIBFT = $(LIBFT_DIR)/libft.a

# Include directories
INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR)/includes

# Colors used for terminal output
GREEN = \033[0;32m
BLUE = \033[0;34m
ORANGE = \033[38;5;214m
RED = \033[0;31m
YELLOW = \033[0;33m
WHITE = \033[0;37m

# Find all source files in src and its subdirectories
SRC = $(shell find $(SRC_DIR) -type f -name "*.c")

# Replace src/ prefix with obj/ and .c suffix with .o
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# Default target
all: $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(WHITE)"

# Rule for creating the project executable
$(NAME): $(OBJ) $(LIBFT)
	@echo "$(BLUE)Building $(NAME)$(WHITE)"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LIBS) -lreadline
	@echo "$(GREEN)$(NAME) created successfully!$(WHITE)"

# Rule for compiling source files to object files in obj directory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@
	@echo "$(GREEN)Compiled $< successfully!$(WHITE)"

# Library rule
$(LIBFT):
	@echo "$(BLUE)Building $(LIBFT)$(WHITE)"
	make -C $(LIBFT_DIR)

# Clean rules
clean:
	@echo "$(RED)Cleaning object files...$(WHITE)"
	rm -rf $(OBJ_DIR)
	rm -f $(NAME)
	make -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(RED)Cleaning binaries...$(WHITE)"
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
