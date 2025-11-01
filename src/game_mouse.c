/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 12:15:16 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/11/01 16:23:15 by aarie-c2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotate_camera(t_game *game, double rot_amount)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->dir_x;
	game->dir_x = game->dir_x * cos(rot_amount) - game->dir_y * sin(rot_amount);
	game->dir_y = old_dir_x * sin(rot_amount) + game->dir_y * cos(rot_amount);
	old_plane_x = game->plane_x;
	game->plane_x = game->plane_x * cos(rot_amount) - game->plane_y * sin(rot_amount);
	game->plane_y = old_plane_x * sin(rot_amount) + game->plane_y * cos(rot_amount);
}

static int	is_large_jump(int delta)
{
	return (abs(delta) >= 50);
}

static void	handle_normal_rotation(t_game *game, int delta_x)
{
	double	rot_amount;

	if (delta_x != 0 && !is_large_jump(delta_x))
	{
		rot_amount = delta_x * game->mouse_sensitivity;
		rotate_camera(game, rot_amount);
	}
}

static void	handle_edge_rotation(t_game *game, int x)
{
	int		edge_margin;
	double	rot_amount;

	edge_margin = 50;
	if (x < edge_margin)
		rot_amount = -0.02;
	else if (x > WIN_W - edge_margin)
		rot_amount = 0.02;
	else
		return ;
	rotate_camera(game, rot_amount);
}

int	mouse_move(int x, int y, t_game *game)
{
	int delta_x;

	(void)y;
	delta_x = x - game->mouse_last_x;
	game->mouse_last_x = x;
	handle_normal_rotation(game, delta_x);
	handle_edge_rotation(game, x);
	return (0);
}
