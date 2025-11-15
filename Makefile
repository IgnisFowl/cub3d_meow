NAME    = cub3d
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -I./include -I./libft/include -Iminilibx-linux
LDFLAGS = -Lminilibx-linux -lmlx_Linux -L/usr/lib -lmlx -lX11 -lXext -lm

SRCDIR  = src
OBJDIR  = obj

SRC_FILES = \
	cats_collision.c \
	cats_hud_draw.c \
	cats_hud_utils.c \
	cats_hud.c \
	cats_init.c \
	cats_parse.c \
	cats_render.c \
	cats_render_utils.c \
	cats_sprite_utils.c \
	cats_sprite.c \
	cats_textures_utils.c \
	cats_textures.c \
	free_all.c \
	free_cats.c \
	game_dda.c \
	game_draw.c \
	game_frame.c \
	game_init.c \
	game_keys.c \
	game_loop.c \
	game_mouse_utils.c \
	game_mouse.c \
	game_raycast.c \
	game_start.c \
	game_textures.c \
	main.c \
	map_final.c \
	map_init.c \
	map_normalizer.c \
	map_parser.c \
	map_rgb.c \
	map_utils.c \
	minimap_draw.c \
	minimap_fov_utils.c \
	minimap_fov.c \
	minimap_tiles.c \
	minimap_utils.c \
	validate_map.c \
	validate_map2.c \
	validate_map3.c \
	validate_playable_map.c \
	win_init.c \
	win_load.c \
	win_textures.c

SRC = $(addprefix $(SRCDIR)/,$(SRC_FILES))

OBJ = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))

LIBFT_DIR = ./libft
LIBFT     = $(LIBFT_DIR)/libft.a

MLX_DIR = ./minilibx-linux
MLX     = $(MLX_DIR)/libmlx_Linux.a

all: $(LIBFT) $(MLX) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -O3 -c $< -o $@

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean || true

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
