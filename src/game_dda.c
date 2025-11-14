/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_dda.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nade-lim <nade-lim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:43:45 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/11/13 15:29:00 by nade-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycast_struct_init(t_raycast *r)
{
	r->camerax = 0;
	r->raydirx = 0;
	r->raydiry = 0;
	r->mapx = 0;
	r->mapy = 0;
	r->sidedistx = 0;
	r->sidedisty = 0;
	r->deltadistx = 0;
	r->deltadisty = 0;
	r->perpwalldist = 0;
	r->stepx = 0;
	r->stepy = 0;
	r->hit = 0;
	r->side = 0;
	r->lineheight = 0;
	r->drawstart = 0;
	r->drawend = 0;
}

static void	dda_step_x(t_game *game)
{
	game->raycast.sidedistx += game->raycast.deltadistx;
	game->raycast.mapx += game->raycast.stepx;
	game->raycast.side = 0;
	if (!is_inside_map(game->map, game->raycast.mapx, game->raycast.mapy))
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
	if (!is_inside_map(game->map, game->raycast.mapx, game->raycast.mapy))
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
