GREEN  = \033[1;32m
YELLOW = \033[1;33m
PURPLE = \033[1;34m
CYAN   = \033[1;36m
BLUE   = \033[1;34m
RESET  = \033[0m
ERASE  = \033[K

NAME = libft.a
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar
ARFLAGS = rcs
INCLUDES = -I$(INC_DIR)

SRC = $(shell find $(SRC_DIR) -name "*.c")
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
HEADER = $(wildcard $(INC_DIR)/*.h)
SUB_DIRS = ft_printf get_next_line

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJ)
	@echo "\n$(GREEN)$(NAME) created$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@printf "\r$(ERASE)$(BLUE)Compiling $(notdir $<)$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@for dir in $(SUB_DIRS); do \
		mkdir -p $(OBJ_DIR)/$$dir; \
	done
	@echo "$(GREEN)obj directory structure created$(RESET)"

clean:
	@echo "$(YELLOW)obj directory removed$(RESET)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(YELLOW)$(NAME) removed$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re