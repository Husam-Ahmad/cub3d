NAME = cub3D	
CC = cc
MLX_DIR = minilibx-linux
CFLAGS = -Wall -Wextra -Werror -I$(MLX_DIR)
MLX = $(MLX_DIR)/libmlx.a
SRC = \
main.c \
main_utils/alg_map_boundaries.c \
main_utils/free_memory.c \
parsing/check_file_data.c \
parsing/process_file_data.c \
parsing/parsing_utils.c \
parsing/map_utils.c \
construct/constructor.c \
hooking/keyhook.c \
hooking/movement.c \
hooking/rotation.c 


OBJ = $(SRC:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(MLX) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBFT) -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c -g $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

cl:
	rm -f *.txt

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(MLX_DIR) clean

re: fclean all

phony: all clean fclean re
