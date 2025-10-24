/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2@c1r4p1.42sp.org.br <aarie-c2@c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 19:03:03 by aarie-c2@c1       #+#    #+#             */
/*   Updated: 2025/10/21 21:15:34 by aarie-c2@c1      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_forward(t_game *game, double move_speed)
{
	int	new_x;
	int	new_y;

	new_x = (int)(game->pos_x + game->dir_x * move_speed);
	new_y = (int)(game->pos_y + game->dir_y * move_speed);
	if (is_inside_map(game->map, new_x, (int)game->pos_y) && \
		game->map->map[(int)game->pos_y][new_x] != '1')
		game->pos_x += game->dir_x * move_speed;
	if (is_inside_map(game->map, (int)game->pos_x, new_y) && \
		game->map->map[new_y][(int)game->pos_x] != '1')
		game->pos_y += game->dir_y * move_speed;
}

static void	move_backward(t_game *game, double move_speed)
{
	int	new_x;
	int	new_y;

	new_x = (int)(game->pos_x - game->dir_x * move_speed);
	new_y = (int)(game->pos_y - game->dir_y * move_speed);
	if (is_inside_map(game->map, new_x, (int)game->pos_y) && \
		game->map->map[(int)game->pos_y][new_x] != '1')
		game->pos_x -= game->dir_x * move_speed;
	if (is_inside_map(game->map, (int)game->pos_x, new_y) && \
		game->map->map[new_y][(int)game->pos_x] != '1')
		game->pos_y -= game->dir_y * move_speed;
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

static void	rotate_left(t_game *game, double rot_speed)
{
	rotate_right(game, -rot_speed);
}

int	game_loop(t_game *game)
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
		rotate_left(game, rot_speed);
	if (game->key_right)
		rotate_right(game, rot_speed);
	draw_frame(game);
	return (0);
}
