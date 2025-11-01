/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 12:15:16 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/11/01 12:34:16 by aarie-c2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	apply_rotation(t_game *game, t_vec *old)
{
	double	cos_a;
	double	sin_a;

	cos_a = cos(old->x);
	sin_a = sin(old->x);
	old->y = game->dir_x;
	game->dir_x = game->dir_x * cos_a - game->dir_y * sin_a;
	game->dir_y = old->y * sin_a + game->dir_y * cos_a;
	old->y = game->plane_x;
	game->plane_x = game->plane_x * cos_a - game->plane_y * sin_a;
	game->plane_y = old->y * sin_a + game->plane_y * cos_a;
}

void    rotate_camera(t_game *game, double angle)
{
	t_vec	old;

	old.x = angle;
	apply_rotation(game, &old);
}
/*
void    handle_mouse(t_game *game)
{
	int		mouse_y;
	int		delta_x;
	double	sensitivity;

	mlx_mouse_get_pos(game->mlx, game->win, &game->mouse_x, &mouse_y);
	if (game->first_mouse)
	{
		game->prev_mouse_x = game->mouse_x;
		game->first_mouse = 0;
		return ;
	}
	delta_x = game->mouse_x - game->prev_mouse_x;
	sensitivity = 0.003;
	rotate_camera(game, delta_x * sensitivity);
	game->prev_mouse_x = game->mouse_x;
}*/

void    handle_mouse(t_game *game)
{
	int		mouse_y;
	int		delta_x;
	double	sensitivity;

	mlx_mouse_get_pos(game->mlx, game->win, &game->mouse_x, &mouse_y);
	if (game->first_mouse)
	{
		game->prev_mouse_x = game->mouse_x;
		game->first_mouse = 0;
		return ;
	}
	delta_x = game->mouse_x - game->prev_mouse_x;
	sensitivity = 0.003;
	rotate_camera(game, delta_x * sensitivity);
	game->prev_mouse_x = game->mouse_x;
}

int     mouse_move(int x, int y, t_game *game)
{
	int		delta_x;
	double	sensitivity;

	(void)y;
	if (game->first_mouse)
	{
		game->prev_mouse_x = x;
		game->first_mouse = 0;
		return (0);
	}
	delta_x = x - game->prev_mouse_x;
	if (delta_x > 100 || delta_x < -100)
	{
		game->prev_mouse_x = x;
		return (0);
	}
	sensitivity = 0.003;
	rotate_camera(game, delta_x * sensitivity);
	game->prev_mouse_x = x;
	return (0);
}
