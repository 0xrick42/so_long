NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
RM = rm -f

MLX_PATH = mlx_linux/
MLX_NAME = $(MLX_PATH)libmlx_Linux.a
MLX_FLAGS = -L$(MLX_PATH) -lmlx_Linux -lXext -lX11 -lm -lz

SRCS = src/main.c src/init.c src/map.c src/validate.c \
       src/render.c src/move.c src/utils.c

OBJS = $(SRCS:.c=.o)

all: $(MLX_NAME) $(NAME)

$(MLX_NAME):
	@make -C $(MLX_PATH)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(MLX_FLAGS) $(CFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	make clean -C $(MLX_PATH)

fclean: clean
	$(RM) $(NAME)
	make clean -C $(MLX_PATH)

re: fclean all

.PHONY: all clean fclean re
