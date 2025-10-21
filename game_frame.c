/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2@c1r4p1.42sp.org.br <aarie-c2@c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:28:04 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/10/21 18:41:15 by aarie-c2@c1      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	raycast_struct_init(t_raycast *r)
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

static void	init_raycast(t_game *game, int x)
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
		draw_column(game, x, game->raycast.drawstart, game->raycast.drawend);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
