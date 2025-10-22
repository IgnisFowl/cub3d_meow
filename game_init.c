/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2@c1r4p1.42sp.org.br <aarie-c2@c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:42:20 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/10/21 21:50:48 by aarie-c2@c1      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_init(t_game *game, t_map *map)
{
	game->mlx = NULL;
	game->win = NULL;
	game->img = NULL;
	game->addr = NULL;
	game->bpp = 0;
	game->line_len = 0;
	game->endian = 0;
	game->map = map;
	game->pos_x = map->player_x + 0.5;
	game->pos_y = map->player_y + 0.5;
	game->dir_x = 0;
	game->dir_y = 0;
	game->plane_x = 0;
	game->plane_y = 0;
	game->key_w = 0;
	game->key_s = 0;
	game->key_a = 0;
	game->key_d = 0;
	game->key_left = 0;
	game->key_right = 0;
}

static void	set_dir_and_plane(t_game *game, t_vec dir, t_vec plane)
{
	game->dir_x = dir.x;
	game->dir_y = dir.y;
	game->plane_x = plane.x;
	game->plane_y = plane.y;
}

void	init_player(t_game *game)
{
	game->pos_x = game->map->player_x + 0.5;
	game->pos_y = game->map->player_y + 0.5;

	if (game->map->player_dir == 'N')
		set_dir_and_plane(game, (t_vec){0.0, -1.0}, (t_vec){0.66, 0.0});
	else if (game->map->player_dir == 'S')
		set_dir_and_plane(game, (t_vec){0.0, 1.0}, (t_vec){-0.66, 0.0});
	else if (game->map->player_dir == 'E')
		set_dir_and_plane(game, (t_vec){1.0, 0.0}, (t_vec){0.0, 0.66});
	else if (game->map->player_dir == 'W')
		set_dir_and_plane(game, (t_vec){-1.0, 0.0}, (t_vec){0.0, -0.66});
}

int	rgb_to_int(int rgb[3])
{
	int	r;
	int	g;
	int	b;

	r = rgb[0];
	g = rgb[1];
	b = rgb[2];
	return ((r << 16) | (g << 8) | b);
}

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	dst = game->addr + (y * game->line_len + x * (game->bpp / 8));
	*(unsigned int *)dst = color;
}
