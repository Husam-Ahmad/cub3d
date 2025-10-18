# Variables
NAME = cub3D	
CC = cc
# CFLAGS = -Wall -Wextra -Werror 
SRC = \
main.c \
alg_map_boundaries.c \
parsing/check_file_data.c \
parsing/process_file_data.c \
parsing/parsing_utils.c \
parsing/map_utils.c \
construct/constructor.c \

OBJ = $(SRC:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

EXEC = cub3D

# Default target
all: $(LIBFT) $(EXEC)

# Link object files to create the executable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) $(LIBFT) -o $(EXEC)

# Compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c -g $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

# Clean up generated files
clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

cl:
	rm -f *.txt

# Remove everything (clean + remove executable)
fclean: clean
	rm -f $(EXEC)
	make -C $(LIBFT_DIR) fclean

# Rebuild everything
re: fclean all

phony: all clean fclean re
