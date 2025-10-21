/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_dda.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2@c1r4p1.42sp.org.br <aarie-c2@c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:43:45 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/10/21 18:43:43 by aarie-c2@c1      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	dda_step_x(t_game *game)
{
	game->raycast.sidedistx += game->raycast.deltadistx;
	game->raycast.mapx += game->raycast.stepx;
	game->raycast.side = 0;
	if (game->raycast.mapx < 0 || game->raycast.mapx >= game->map->width || \
		game->raycast.mapy < 0 || game->raycast.mapy >= game->map->height)
	{
		game->raycast.hit = 1;
		return ;
	}
	if (game->map->map[game->raycast.mapy][game->raycast.mapx] == '1')
		game->raycast.hit = 1;
}

static void	dda_step_y(t_game *game)
{
	game->raycast.sidedisty += game->raycast.deltadisty;
	game->raycast.mapy += game->raycast.stepy;
	game->raycast.side = 1;
	if (game->raycast.mapx < 0 || game->raycast.mapx >= game->map->width || \
		game->raycast.mapy < 0 || game->raycast.mapy >= game->map->height)
	{
		game->raycast.hit = 1;
		return ;
	}
	if (game->map->map[game->raycast.mapy][game->raycast.mapx] == '1')
		game->raycast.hit = 1;
}

void	perform_dda(t_game *game)
{
	while (!game->raycast.hit)
	{
		if (game->raycast.sidedistx < game->raycast.sidedisty)
			dda_step_x(game);
		else
			dda_step_y(game);
	}
}

void	calculate_draw_bound(t_game *game)
{
	if (game->raycast.side == 0)
		game->raycast.perpwalldist = (game->raycast.mapx - game->pos_x \
			+ (1 - game->raycast.stepx) / 2) / game->raycast.raydirx;
	else
		game->raycast.perpwalldist = (game->raycast.mapy - game->pos_y \
			+ (1 - game->raycast.stepy) / 2) / game->raycast.raydiry;
	game->raycast.lineheight = (int)(WIN_H / game->raycast.perpwalldist);
	game->raycast.drawstart = -game->raycast.lineheight / 2 + WIN_H / 2;
	if (game->raycast.drawstart < 0)
		game->raycast.drawstart = 0;

	game->raycast.drawend = game->raycast.lineheight / 2 + WIN_H / 2;
	if (game->raycast.drawend >= WIN_H)
		game->raycast.drawend = WIN_H - 1;
}
