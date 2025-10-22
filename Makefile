NAME = cub3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iminilibx-linux -I./include
LDFLAGS = -Lminilibx-linux -lmlx_Linux -L/usr/lib -lmlx -lX11 -lXext

SRC = main.c map_parser.c map_init.c map_final.c free_all.c map_utils.c game_init.c game_frame.c game_dda.c game_draw.c game_move.c game_keys.c game_textures.c game_start.c
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = ./minilibx-linux
MLX = $(MLX_DIR)/libmlx_Linux.a

all: $(LIBFT) $(MLX) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compile object files and ensure obj directory exists
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -O3 -c $< -o $@

# Build the main executable
$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean || true

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
