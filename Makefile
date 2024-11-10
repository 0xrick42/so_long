NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
RM = rm -f

# MLX configuration
MLX_PATH = mlx_linux/
MLX_NAME = $(MLX_PATH)libmlx_Linux.a
MLX_FLAGS = -L$(MLX_PATH) -lmlx_Linux -lXext -lX11 -lm -lz

# Directories
OBJ_DIR = obj/

# Headers
HEADERS = includes/so_long.h

# Source files
SRCS = src/main.c \
       src/init.c \
       src/map.c \
       src/check_maps.c \
       src/validate.c \
       src/render.c \
       src/move.c \
       src/utils.c \
       src/flood_fill.c

# Object files with proper directory
OBJS = $(SRCS:src/%.c=$(OBJ_DIR)%.o)

# Default target
all: $(NAME)

# Create obj directory and ensure MLX is compiled first
$(NAME): $(OBJ_DIR) $(MLX_NAME) $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(MLX_FLAGS) $(CFLAGS)

# MLX compilation
$(MLX_NAME):
	@echo "Compiling MLX..."
	@cd $(MLX_PATH) && ./configure > /dev/null 2>&1
	@make -C $(MLX_PATH) > /dev/null 2>&1

# Create obj directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Pattern rule for object files
$(OBJ_DIR)%.o: src/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(MLX_PATH) -c $< -o $@

# Clean objects
clean:
	$(RM) -r $(OBJ_DIR)
	@make clean -C $(MLX_PATH) > /dev/null 2>&1

# Clean everything
fclean: clean
	$(RM) $(NAME)
	@cd $(MLX_PATH) && make clean > /dev/null 2>&1

# Full rebuild
re: fclean all

.PHONY: all clean fclean re