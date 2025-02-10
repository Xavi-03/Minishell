NAME = minishell
CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror -g -I env
LIBFTDIR = libft/
OBJ_DIR = obj/

# Source files (recursive search)
SRC = $(shell find src -name '*.c')
# Object files (mirror directory structure in OBJ_DIR)
OBJ = $(SRC:src/%.c=$(OBJ_DIR)%.o)

# Include and library paths
INCLUDES = -Iincludes -I$(LIBFTDIR)
LIBS = -L$(LIBFTDIR) -lft -lreadline

# Colors for better output
GREEN = \033[0;32m
RED = \033[0;31m
NC = \033[0m

# Build libft first
$(LIBFTDIR)libft.a:
	@make -C $(LIBFTDIR)

# Rule to compile object files
$(OBJ_DIR)%.o: src/%.c includes/minishell.h | $(LIBFTDIR)libft.a
	@mkdir -p $(dir $@)
	@echo "$(GREEN)Compiling$(NC) $<"
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

# Main build rule
$(NAME): $(OBJ)
	@echo "$(GREEN)Linking$(NC) $@"
	@$(CC) $(FLAGS) $^ -o $@ $(LIBS)
	@echo "$(GREEN)Build completed!$(NC)"

# Standard targets
all: $(NAME)

clean:
	@$(RM) -r $(OBJ_DIR)
	@make -C $(LIBFTDIR) clean
	@echo "$(RED)Cleaned object files$(NC)"

fclean: clean
	@$(RM) $(NAME)
	@make -C $(LIBFTDIR) fclean
	@echo "$(RED)Removed executable$(NC)"

re: fclean all

.PHONY: all clean fclean re
