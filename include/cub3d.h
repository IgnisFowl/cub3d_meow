/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2@c1r4p1.42sp.org.br <aarie-c2@c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:07:16 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/10/24 16:29:27 by aarie-c2@c1      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <X11/keysym.h>

# include "../libft/include/ft_printf.h"
# include "../libft/include/get_next_line.h"
# include "../libft/include/libft.h"
# include "../minilibx-linux/mlx.h"

# define WIN_W 1280
# define WIN_H 720

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_map
{
	char	*texture_north;
	char	*texture_south;
	char	*texture_west;
	char	*texture_east;
	int		color_floor[3];
	int		color_ceiling[3];
	int		width;
	int		height;
	char	**map;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_map;

typedef struct s_raycast
{
	double	camerax;
	double	raydirx;
	double	raydiry;
	int		mapx;
	int		mapy;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	int		lineheight;
	int		drawstart;
	int		drawend;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
}	t_raycast;

typedef struct s_game
{
	t_map		*map;
	t_raycast	raycast;
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	int			key_w;
	int			key_s;
	int			key_a;
	int			key_d;
	int			key_left;
	int			key_right;
	t_texture	texture_north;
	t_texture	texture_south;
	t_texture	texture_west;
	t_texture	texture_east;
}	t_game;

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

void	map_init(t_map *map);
void	start_map(char *argv, t_map *map);
int		array_len(char **array);
int		is_map_line(char *line);
int		is_inside_map(t_map *map, int x, int y);
void	add_map_line(char ***map_lines, char *line);
int		parse_texture(t_map *map, char *line);
int		parse_rgb(t_map *map, char *line);
void	finalize_map(t_map *map, char **map_lines);
void	normalize_map(t_map *map);

void	start_game(t_map *map, t_game *game);
void	draw_frame(t_game *game);
void	perform_dda(t_game *game);
void	calculate_draw_bound(t_game *game);
void	draw_column(t_game *game, int x, int drawStart, int drawEnd);

int		game_loop(t_game *game);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
void	strafe_left(t_game *game, double move_speed);
void	strafe_right(t_game *game, double move_speed);

void	init_player(t_game *game);
void	game_init(t_game *game, t_map *map);
void	prepare_texture_params(t_game *game);
int		rgb_to_int(int rgb[3]);
void	my_mlx_pixel_put(t_game *game, int x, int y, int color);
void	load_all_textures(t_game *game, t_map *map);

void	exit_with_error(char *msg, t_map *map, t_game *game, char *str);
void	free_map(t_map *map);
void	free_arr(char ***arr);
int		close_window(t_game *game);

void	print_map(const t_map *map); //deletar depois

#endif