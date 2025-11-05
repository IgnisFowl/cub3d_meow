/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aline-arthur <aline-arthur@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 23:25:14 by aline-arthu       #+#    #+#             */
/*   Updated: 2025/11/04 23:25:38 by aline-arthu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_raycast_dir_map(t_game *game, int x)
{
	game->raycast.camerax = 2.0 * x / (double)WIN_W - 1;
	game->raycast.raydirx = game->dir_x + game->plane_x * game->raycast.camerax;
	game->raycast.raydiry = game->dir_y + game->plane_y * game->raycast.camerax;
	game->raycast.mapx = (int)game->pos_x;
	game->raycast.mapy = (int)game->pos_y;
}

static void	init_raycast_steps_sidedist(t_game *game)
{
	if (game->raycast.raydirx < 0)
	{
		game->raycast.stepx = -1;
		game->raycast.sidedistx = (game->pos_x - game->raycast.mapx) * \
		game->raycast.deltadistx;
	}
	else
	{
		game->raycast.stepx = 1;
		game->raycast.sidedistx = (game->raycast.mapx + 1.0 - game->pos_x) * \
		game->raycast.deltadistx;
	}
	if (game->raycast.raydiry < 0)
	{
		game->raycast.stepy = -1;
		game->raycast.sidedisty = (game->pos_y - game->raycast.mapy) * \
		game->raycast.deltadisty;
	}
	else
	{
		game->raycast.stepy = 1;
		game->raycast.sidedisty = (game->raycast.mapy + 1.0 - game->pos_y) * \
		game->raycast.deltadisty;
	}
}

void	init_raycast(t_game *game, int x)
{
	init_raycast_dir_map(game, x);
	if (game->raycast.raydirx == 0)
		game->raycast.deltadistx = 1e30;
	else
		game->raycast.deltadistx = fabs(1 / game->raycast.raydirx);
	if (game->raycast.raydiry == 0)
		game->raycast.deltadisty = 1e30;
	else
		game->raycast.deltadisty = fabs(1 / game->raycast.raydiry);
	init_raycast_steps_sidedist(game);
	game->raycast.hit = 0;
}
