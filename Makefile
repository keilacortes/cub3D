NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

OBJ_DIR = obj

LIBFT_DIR = libs/libft
LIBFT	  = $(LIBFT_DIR)/libft.a

MLX_DIR = libs/minilibx
MLX		= $(MLX_DIR)/libmlx_Linux.a

SRCS = $(addprefix srcs/, main.c \
						  cub3d_utils.c \
						  cleanup_game.c \
						  controls/hooks.c \
						  controls/movement.c \
						  controls/minimap.c \
						  parse/parse_file.c \
						  parse/parse_utils.c \
						  parse/parse_map.c \
						  parse/validate_map.c \
						  parse/validate_tex.c \
)

OBJS = $(SRCS:srcs/%.c=$(OBJ_DIR)/%.o)

INC = -I./inc \
	  -I$(LIBFT_DIR)/inc \
	  -I$(MLX_DIR)

GREEN  = \033[0;32m
YELLOW = \033[1;33m
RED    = \033[0;31m
BLUE   = \033[0;34m
RESET  = \033[0m

all: $(LIBFT) $(MLX) $(NAME)

$(LIBFT):
	@echo "$(BLUE)Compiling libft...$(RESET)"
	@make -C $(LIBFT_DIR) --no-print-directory

$(MLX):
	@echo "$(BLUE)Compiling MiniLibX...$(RESET)"
	@make -C $(MLX_DIR) --no-print-directory

$(OBJ_DIR)/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) \
		-L$(LIBFT_DIR) -lft \
		-L$(MLX_DIR) -lmlx_Linux \
		-L/usr/lib -lXext -lX11 -lm -lz \
		-o $(NAME)
	@echo "$(GREEN)Compiled successfully!$(RESET)"

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@make clean -C $(LIBFT_DIR) --no-print-directory
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(RED)Full cleaning...$(RESET)"
	@make fclean -C $(LIBFT_DIR) --no-print-directory
	@rm -f $(NAME)

re: fclean all

VALGRIND_FLAGS = --leak-check=full \
				 --show-leak-kinds=all \
				 --track-origins=yes \
				 --suppressions=valgrind.supp

valgrind: $(NAME)
	@echo "$(BLUE)Running with Valgrind...$(RESET)"
	@valgrind $(VALGRIND_FLAGS) ./$(NAME) $(ARGS)

.PHONY: all clean fclean re