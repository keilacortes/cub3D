NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libs/libft
LIBFT	  = $(LIBFT_DIR)/libft.a

MLX_DIR = libs/minilibx
MLX		= $(MLX_DIR)/libmlx_Linux.a

SRCS = $(addprefix srcs/, main.c \
						  cub3d_utils.c \
)

OBJS = $(SRCS:.c=.o)

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

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) \
		-L$(LIBFT_DIR) -lft \
		-L$(MLX_DIR) -lmlx_Linux \
		-L/usr/lib -lXext -lX11 -lm -lz \
		-o $(NAME)
	@echo "$(GREEN)Compiled successfully!$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) $(INC) -O3 -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@make clean -C $(LIBFT_DIR) --no-print-directory
	@rm -f $(OBJS)

fclean: clean
	@echo "$(RED)Full cleaning...$(RESET)"
	@make fclean -C $(LIBFT_DIR) --no-print-directory
	@rm -f $(NAME)

re: fclean all

VALGRIND_FLAGS = --leak-check=full \
				 --show-leak-kinds=all \
				 --track-origins=yes

valgrind: $(NAME)
	@echo "$(BLUE)Running with Valgrind...$(RESET)"
	@valgrind $(VALGRIND_FLAGS) ./$(NAME) $(ARGS)

.PHONY: all clean fclean re