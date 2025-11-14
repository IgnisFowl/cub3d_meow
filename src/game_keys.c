/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nade-lim <nade-lim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 19:12:08 by aarie-c2@c1       #+#    #+#             */
/*   Updated: 2025/11/14 17:31:53 by nade-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (game->game_started == 0)
	{
		game->game_started = 1;
		return (0);
	}
	if (keycode == XK_w)
		game->key_w = 1;
	else if (keycode == XK_s)
		game->key_s = 1;
	else if (keycode == XK_a)
		game->key_a = 1;
	else if (keycode == XK_d)
		game->key_d = 1;
	else if (keycode == XK_Left)
		game->key_left = 1;
	else if (keycode == XK_Right)
		game->key_right = 1;
	else if (keycode == 32)
		try_collect_cat(game);
	else if (keycode == XK_Escape)
		close_window(game);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == XK_w)
		game->key_w = 0;
	else if (keycode == XK_s)
		game->key_s = 0;
	else if (keycode == XK_a)
		game->key_a = 0;
	else if (keycode == XK_d)
		game->key_d = 0;
	else if (keycode == XK_Left)
		game->key_left = 0;
	else if (keycode == XK_Right)
		game->key_right = 0;
	return (0);
}

void	strafe_left(t_game *game, double move_speed)
{
	double	perp_dir_x;
	double	perp_dir_y;
	double	nx;
	double	ny;
	double	pad;

	pad = 0.3;
	perp_dir_x = game->dir_y;
	perp_dir_y = -game->dir_x;
	nx = game->pos_x + perp_dir_x * move_speed;
	ny = game->pos_y + perp_dir_y * move_speed;
	if (game->map->map[(int)game->pos_y][(int)(nx + pad)] != '1' &&
		game->map->map[(int)game->pos_y][(int)(nx - pad)] != '1')
		game->pos_x = nx;
	if (game->map->map[(int)(ny + pad)][(int)game->pos_x] != '1' &&
		game->map->map[(int)(ny - pad)][(int)game->pos_x] != '1')
		game->pos_y = ny;
}

void	strafe_right(t_game *game, double move_speed)
{
	double	perp_dir_x;
	double	perp_dir_y;
	double	nx;
	double	ny;
	double	pad;

	pad = 0.3;
	perp_dir_x = -game->dir_y;
	perp_dir_y = game->dir_x;
	nx = game->pos_x + perp_dir_x * move_speed;
	ny = game->pos_y + perp_dir_y * move_speed;
	if (game->map->map[(int)game->pos_y][(int)(nx + pad)] != '1' &&
		game->map->map[(int)game->pos_y][(int)(nx - pad)] != '1')
		game->pos_x = nx;
	if (game->map->map[(int)(ny + pad)][(int)game->pos_x] != '1' &&
		game->map->map[(int)(ny - pad)][(int)game->pos_x] != '1')
		game->pos_y = ny;
}
