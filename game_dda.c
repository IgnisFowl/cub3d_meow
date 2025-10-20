/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_dda.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:43:45 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/10/20 09:56:29 by aarie-c2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void dda_step_x(t_game *game)
{
	game->raycast.sideDistX += game->raycast.deltaDistX;
	game->raycast.mapX += game->raycast.stepX;
	game->raycast.side = 0;
	if (game->raycast.mapX < 0 || game->raycast.mapX >= game->map->width ||
		game->raycast.mapY < 0 || game->raycast.mapY >= game->map->height)
	{
		game->raycast.hit = 1;
		return;
	}
	if (game->map->map[game->raycast.mapY][game->raycast.mapX] == '1')
		game->raycast.hit = 1;
}

static void	dda_step_y(t_game *game)
{
	game->raycast.sideDistY += game->raycast.deltaDistY;
	game->raycast.mapY += game->raycast.stepY;
	game->raycast.side = 1;
	if (game->raycast.mapX < 0 || game->raycast.mapX >= game->map->width ||
		game->raycast.mapY < 0 || game->raycast.mapY >= game->map->height)
	{
		game->raycast.hit = 1;
		return;
	}
	if (game->map->map[game->raycast.mapY][game->raycast.mapX] == '1')
		game->raycast.hit = 1;
}

void	perform_dda(t_game *game)
{
	while (!game->raycast.hit)
	{
		if (game->raycast.sideDistX < game->raycast.sideDistY)
			dda_step_x(game);
		else
			dda_step_y(game);
	}
}

void	calculate_draw_bound(t_game *game)
{
	if (game->raycast.side == 0)
		game->raycast.perpWallDist = (game->raycast.mapX - game->pos_x
			+ (1 - game->raycast.stepX) / 2) / game->raycast.rayDirX;
	else
		game->raycast.perpWallDist = (game->raycast.mapY - game->pos_y
			+ (1 - game->raycast.stepY) / 2) / game->raycast.rayDirY;
	game->raycast.lineHeight = (int)(WIN_H / game->raycast.perpWallDist);
	game->raycast.drawStart = -game->raycast.lineHeight / 2 + WIN_H / 2;
	if (game->raycast.drawStart < 0)
		game->raycast.drawStart = 0;

	game->raycast.drawEnd = game->raycast.lineHeight / 2 + WIN_H / 2;
	if (game->raycast.drawEnd >= WIN_H)
		game->raycast.drawEnd = WIN_H - 1;
}
