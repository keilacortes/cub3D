NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT = libft/libft.a

SRCS = $(addprefix srcs/, main.c \
						  )

OBJS = $(SRCS:.c=.o)

GREEN = \033[0;32m
YELLOW = \033[1;33m
RED = \033[0;31m
BLUE = \033[0;34m
RESET = \033[0m

all: $(LIBFT) $(NAME)

$(LIBFT):
	@echo "$(BLUE)Compiling libft...$(RESET)"
	@make -C libft --no-print-directory

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -L./libft -lft -o $(NAME)
	@echo "$(GREEN)Compiled successfuly!$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -I./inc -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@make clean -C ./libft --no-print-directory
	@rm -f $(OBJS)

fclean: clean
	@echo "$(RED)Full cleaning...$(RESET)"
	@make fclean -C ./libft --no-print-directory
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re