/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nade-lim <nade-lim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 19:03:03 by aarie-c2@c1       #+#    #+#             */
/*   Updated: 2025/11/14 17:31:11 by nade-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_forward(t_game *game, double speed)
{
	double	nx;
	double	ny;
	double	pad;

	pad = 0.3;
	nx = game->pos_x + game->dir_x * speed;
	ny = game->pos_y + game->dir_y * speed;
	if (game->map->map[(int)game->pos_y][(int)(nx + pad)] != '1' &&
		game->map->map[(int)game->pos_y][(int)(nx - pad)] != '1')
		game->pos_x = nx;
	if (game->map->map[(int)(ny + pad)][(int)game->pos_x] != '1' &&
		game->map->map[(int)(ny - pad)][(int)game->pos_x] != '1')
		game->pos_y = ny;
}

static void	move_backward(t_game *game, double speed)
{
	double	nx;
	double	ny;
	double	pad;

	pad = 0.3;
	nx = game->pos_x - game->dir_x * speed;
	ny = game->pos_y - game->dir_y * speed;
	if (game->map->map[(int)game->pos_y][(int)(nx + pad)] != '1' &&
		game->map->map[(int)game->pos_y][(int)(nx - pad)] != '1')
		game->pos_x = nx;
	if (game->map->map[(int)(ny + pad)][(int)game->pos_x] != '1' &&
		game->map->map[(int)(ny - pad)][(int)game->pos_x] != '1')
		game->pos_y = ny;
}

static void	rotate_right(t_game *game, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->dir_x;
	game->dir_x = game->dir_x * cos(rot_speed) - game->dir_y * sin(rot_speed);
	game->dir_y = old_dir_x * sin(rot_speed) + game->dir_y * cos(rot_speed);
	old_plane_x = game->plane_x;
	game->plane_x = game->plane_x * cos(rot_speed) - \
		game->plane_y * sin(rot_speed);
	game->plane_y = old_plane_x * sin(rot_speed) + \
		game->plane_y * cos(rot_speed);
}

static void	handle_movement(t_game *game)
{
	double	move_speed;
	double	rot_speed;

	move_speed = 0.05;
	rot_speed = 0.03;
	if (game->key_w)
		move_forward(game, move_speed);
	if (game->key_s)
		move_backward(game, move_speed);
	if (game->key_a)
		strafe_left(game, move_speed);
	if (game->key_d)
		strafe_right(game, move_speed);
	if (game->key_left)
		rotate_right(game, -rot_speed);
	if (game->key_right)
		rotate_right(game, rot_speed);
}

int	game_loop(t_game *game)
{
	check_snack_pickup(game);
	update_animations(game);
	handle_movement(game);
	draw_frame(game);
	if (game->game_won)
	{
		render_win_animation(game);
		if (game->win_timer > 300)
			close_window(game);
		return (0);
	}
	return (0);
}
