NAME    = cub3d
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -I./include -I./libft/include -Iminilibx-linux
LDFLAGS = -Lminilibx-linux -lmlx_Linux -L/usr/lib -lmlx -lX11 -lXext

SRCDIR  = src
OBJDIR  = obj

# List sources RELATIVE to SRCDIR (no wildcards)
SRC_FILES = \
	free_all.c \
	game_dda.c \
	game_draw.c \
	game_frame.c \
	game_init.c \
	game_keys.c \
	game_move.c \
	game_start.c \
	game_textures.c \
	main.c \
	map_final.c \
	map_init.c \
	map_normalizer.c \
	map_parser.c \
	map_utils.c \
	minimap_draw.c \
	minimap_tiles.c \
	minimap_utils.c

# Prepend SRCDIR/ to each file
SRC = $(addprefix $(SRCDIR)/,$(SRC_FILES))

# Map src/foo.c -> obj/foo.o (preserves any subfolders present)
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

# Ensure obj subdirs exist per source's path
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
