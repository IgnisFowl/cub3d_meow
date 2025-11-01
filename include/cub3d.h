/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:07:16 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/11/01 12:22:33 by aarie-c2         ###   ########.fr       */
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
# define COLOR_WALL 0x333333
# define COLOR_FLOOR 0x101010
# define COLOR_VISIBLE 0xFFFFFF
# define COLOR_PLAYER 0x00FF1493
# define COLOR_DARK 0x000000
# define COLOR_FOV_TRIANGLE 0x00FFB6C1 
# define TILE_SIZE 8
# define LIGHT_RADIUS 5 

typedef struct s_fov
{
	int player_px;
	int player_py;
	int end_left_x;
	int end_left_y;
	int end_right_x;
	int end_right_y;
}	t_fov;

typedef struct s_triangle
{
	int x0, y0;
	int x1, y1;
	int x2, y2;
}	t_triangle;

typedef struct s_tri_bounds
{
	int min_x, max_x;
	int min_y, max_y;
}	t_tri_bounds;

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

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		w;
	int		h;
}	t_img;

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
	t_img		*imgt;
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
	int			mouse_x;
	int			prev_mouse_x;
	int			first_mouse;
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

void	minimap_present(t_game *g, int sx, int sy);
void	draw_minimap(t_game *g);
void	minimap_put_px(t_game *g, int x, int y, int color);
int		c_str_len(const char *s);
int		minimap_init(t_game *g);
void	minimap_draw_tile(t_game *g, int tx, int ty, int color);
int		minimap_tile_color(t_game *g, int x, int y);
void	init_fov_pos(t_game *g, t_fov *f);
void	calc_fov_edges(t_game *g, t_fov *f);
void 	fov_to_triangle(t_fov *f, t_triangle *t);
void 	tri_bounds(t_triangle *t, t_tri_bounds *b);
int 	point_in_tri(t_triangle *t, int x, int y);
void	draw_minimap_fov(t_game *g);

void	handle_mouse(t_game *game);
void	rotate_camera(t_game *game, double angle);
int		mouse_move(int x, int y, t_game *game);
void	apply_rotation(t_game *game, t_vec *old);

void	exit_with_error(char *msg, t_map *map, t_game *game, char *str);
void	free_map(t_map *map);
void	free_arr(char ***arr);
int		close_window(t_game *game);

void	print_map(const t_map *map); //deletar depois

#endif