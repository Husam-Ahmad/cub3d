# Project
NAME	= cub3D
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
CPPFLAGS= -I minilibx-linux -I libft
LDLIBS	= -lm -lX11 -lXext

LIBFT_DIR	= libft
MLX_DIR		= minilibx-linux

# Libs
LIBFT		= $(LIBFT_DIR)/libft.a
MLX			= $(MLX_DIR)/libmlx_Linux.a

# Sources
SRC := \
  main.c \
  parsing/check_file_data.c \
  parsing/process_file_data.c \
  parsing/parsing_utils.c \
  construct/constructor.c

OBJ := $(SRC:.c=.o)

# Default target
all: $(NAME)

# Link
$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(OBJ) $(LIBFT) $(MLX) $(LDFLAGS) $(LDLIBS) -o $@

# Compile
%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Build libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Build mlx (linux)
$(MLX):
	$(MAKE) -C $(MLX_DIR)

# Clean objects
clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean || true
	$(MAKE) -C $(MLX_DIR) clean || true

# Extra local cleanup (your custom)
cl:
	rm -f *.txt

# Full clean
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean || true

# Rebuild
re: fclean all

.PHONY: all clean fclean re cl
