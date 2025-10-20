/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:28:04 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/10/20 09:55:23 by aarie-c2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	raycast_struct_init(t_raycast *r)
{
	r->cameraX = 0;
	r->rayDirX = 0;
	r->rayDirY = 0;
	r->mapX = 0;
	r->mapY = 0;
	r->sideDistX = 0;
	r->sideDistY = 0;
	r->deltaDistX = 0;
	r->deltaDistY = 0;
	r->perpWallDist = 0;
	r->stepX = 0;
	r->stepY = 0;
	r->hit = 0;
	r->side = 0;
	r->lineHeight = 0;
	r->drawStart = 0;
	r->drawEnd = 0;
}

static void	init_raycast_dir_map(t_game *game, int x)
{
	game->raycast.cameraX = 2.0 * x / (double)WIN_W - 1;
	game->raycast.rayDirX = game->dir_x + game->plane_x * game->raycast.cameraX;
	game->raycast.rayDirY = game->dir_y + game->plane_y * game->raycast.cameraX;
	game->raycast.mapX = (int)game->pos_x;
	game->raycast.mapY = (int)game->pos_y;
}

static void	init_raycast_steps_sidedist(t_game *game)
{
	if (game->raycast.rayDirX < 0)
	{
		game->raycast.stepX = -1;
		game->raycast.sideDistX = (game->pos_x - game->raycast.mapX) * game->raycast.deltaDistX;
	}
	else
	{
		game->raycast.stepX = 1;
		game->raycast.sideDistX = (game->raycast.mapX + 1.0 - game->pos_x) * game->raycast.deltaDistX;
	}
	if (game->raycast.rayDirY < 0)
	{
		game->raycast.stepY = -1;
		game->raycast.sideDistY = (game->pos_y - game->raycast.mapY) * game->raycast.deltaDistY;
	}
	else
	{
		game->raycast.stepY = 1;
		game->raycast.sideDistY = (game->raycast.mapY + 1.0 - game->pos_y) * game->raycast.deltaDistY;
	}
}

static void	init_raycast(t_game *game, int x)
{
	init_raycast_dir_map(game, x);
	if (game->raycast.rayDirX == 0)
		game->raycast.deltaDistX = 1e30;
	else
		game->raycast.deltaDistX = fabs(1 / game->raycast.rayDirX);
	if (game->raycast.rayDirY == 0)
		game->raycast.deltaDistY = 1e30;
	else
		game->raycast.deltaDistY = fabs(1 / game->raycast.rayDirY);
	init_raycast_steps_sidedist(game);
	game->raycast.hit = 0;
}

void	draw_frame(t_game *game)
{
	int	x;

	x = 0;
	raycast_struct_init(&game->raycast);
	while (x < WIN_W)
	{
		init_raycast(game, x);
		perform_dda(game);
		calculate_draw_bound(game);
		draw_column(game, x, game->raycast.drawStart, game->raycast.drawEnd);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
