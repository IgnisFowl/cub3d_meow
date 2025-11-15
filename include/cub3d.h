/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aline-arthur <aline-arthur@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:07:16 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/11/15 13:29:14 by aline-arthu      ###   ########.fr       */
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

# define WIN_W 1920
# define WIN_H 1080
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
	int	player_px;
	int	player_py;
	int	end_left_x;
	int	end_left_y;
	int	end_right_x;
	int	end_right_y;
}	t_fov;

typedef struct s_triangle
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	x2;
	int	y2;
}	t_triangle;

typedef struct s_tri_bounds
{
	int	min_x;
	int	max_x;
	int	min_y;
	int	max_y;
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

typedef struct s_sprite
{
	double	x;
	double	y;
	int		type;
	int		active;
	int		frame;
	double	dist;
}	t_sprite;

typedef struct s_spr_calc
{
	double	spr_x;
	double	spr_y;
	double	inv_det;
	double	trans_x;
	double	trans_y;
	int		screen_x;
	int		height;
	int		width;
	int		draw_start_y;
	int		draw_end_y;
	int		draw_start_x;
	int		draw_end_x;
}	t_spr_calc;

typedef struct s_cats
{
	t_sprite	*cats;
	t_sprite	*snacks;
	int			num_cats;
	int			num_snacks;
	int			snacks_inv;
	double		anim_time;
	t_texture	cat_textures[9][3];
	t_texture	snack_texture;
}	t_cats;

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

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

typedef struct s_firework
{
	t_texture	textures[7];
	int			x;
	int			y;
	int			current_frame;
}	t_firework;

typedef struct s_firework_draw
{
	t_firework	*fw;
	t_texture	*tex;
	int			tex_x;
	int			tex_y;
	int			screen_x;
	int			screen_y;
}	t_firework_draw;

typedef struct s_win_draw
{
	t_texture	*tex;
	int			tex_x;
	int			tex_y;
	int			screen_x;
	int			screen_y;
}	t_win_draw;

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
	int			mouse_last_x;
	double		*z_buffer;
	float		mouse_sensitivity;
	t_cats		cats;
	int			game_won;
	int			win_timer;
	t_firework	fireworks[3];
	t_texture	win_screen;
	int			game_started;
	void		*start_img;
}	t_game;

typedef struct s_lim
{
	int	h;
	int	w;
}	t_lim;

void		map_init(t_map *map);
void		start_map(char *argv, t_game *game);
int			array_len(char **array);
int			is_map_line(char *line);
int			is_inside_map(t_map *map, int x, int y);
void		add_map_line(char ***map_lines, char *line);
int			parse_texture(t_map *map, char *line);
int			parse_rgb(t_game *game, char *trimmed);
void		finalize_map(t_game *game, char **map_lines);
void		normalize_map(t_game *game);

void		start_game(t_game *game);
void		draw_frame(t_game *game);
void		perform_dda(t_game *game);
void		calculate_draw_bound(t_game *game);
void		draw_column(t_game *game, int x, int drawStart, int drawEnd);

int			game_loop(t_game *game);
int			key_press(int keycode, t_game *game);
int			key_release(int keycode, t_game *game);
void		strafe_left(t_game *game, double move_speed);
void		strafe_right(t_game *game, double move_speed);

void		init_player(t_game *game);
void		game_init(t_game *game, t_map *map);
void		prepare_texture_params(t_game *game);
int			rgb_to_int(int rgb[3]);
void		my_mlx_pixel_put(t_game *game, int x, int y, int color);
void		load_all_textures(t_game *game);
void		raycast_struct_init(t_raycast *r);
void		init_raycast(t_game *game, int x);

void		minimap_present(t_game *g, int sx, int sy);
void		draw_minimap(t_game *g);
void		minimap_put_px(t_game *g, int x, int y, int color);
int			c_str_len(const char *s);
int			minimap_init(t_game *g);
void		minimap_draw_tile(t_game *g, int tx, int ty, int color);
int			minimap_tile_color(t_game *g, int x, int y);
void		init_fov_pos(t_game *g, t_fov *f);
void		calc_fov_edges(t_game *g, t_fov *f);
void		fov_to_triangle(t_fov *f, t_triangle *t);
void		tri_bounds(t_triangle *t, t_tri_bounds *b);
int			point_in_tri(t_triangle *t, int x, int y);
void		draw_minimap_fov(t_game *g);

int			mouse_move(int x, int y, t_game *game);
int			focus_in(t_game *game);
int			focus_out(t_game *game);

void		clear_cats_from_map(t_game *game);
void		parse_cats(t_game *game);
void		init_cats(t_game *game);
void		load_cats_textures(t_game *game);
void		update_animations(t_game *game);
void		check_snack_pickup(t_game *game);
void		try_collect_cat(t_game *game);
void		render_sprites(t_game *game);
void		draw_one_sprite(t_game *g, t_sprite *s, t_texture *tex);
void		put_sprite_pixel(t_game *g, int x, int y, int color);
int			get_tex_pixel(t_texture *tex, int x, int y);
void		calc_sprite_bounds(t_spr_calc *c);
void		calc_sprite_screen(t_spr_calc *c);
void		init_sprite_calc(t_game *g, t_sprite *s, t_spr_calc *c);
void		update_all_distances(t_game *game);
void		sort_all_sprites(t_game *game);
void		draw_hud_pixel(t_game *g, int x, int y, int color);
void		draw_cat_pixel(t_game *g, int x, int y);
void		draw_snack_pixel(t_game *g, int x, int y);
int			get_snack_tex_pixel(t_game *g, int tex_x, int tex_y);
int			get_collected_cats(t_game *game);
void		draw_hud(t_game *g);
void		draw_hud_box(t_game *g);
void		draw_snack_icon(t_game *g);
void		draw_cat_icon(t_game *g);
const char	*get_cat_path(int type, int frame);
void		check_win_condition(t_game *game);
void		load_fireworks_textures(t_game *game);
void		render_win_animation(t_game *game);
void		draw_loop(t_game *game, t_firework_draw *draw);
void		load_win_screen(t_game *game);
void		draw_win_screen(t_game *game);

void		exit_with_error(char *msg, t_game *game, char *str);
void		free_map(t_map *map);
void		free_arr(char ***arr);
void		free_cats(t_game *game);
int			close_window(t_game *game);

void		validate_map(t_game *game, char **map_lines);
void		validate_cub_extension(char *filename, t_game *game);
int			validate_config(t_game *game);
int			line_is_blank(const char *s);
void		check_required_colors(t_game *game);
int			check_walls_closed(t_game *game);
void		sanitize_map_lines(char **map_lines);
void		clean_trailing_lines(t_game *game, char **map_lines);
void		check_playable_map(t_game *game);
int			is_only_digits(char *s);

void		print_welcome_message(void);

#endif