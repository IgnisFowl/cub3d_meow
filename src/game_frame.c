/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:28:04 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/11/01 15:33:03 by aarie-c2         ###   ########.fr       */
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

static void	draw_frame_continue(t_game *game)
{
	render_sprites(game);
	draw_minimap(game);
	draw_snack_icon(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	minimap_present(game, 16, 16);
	draw_snack_text(game);
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
        if (x >= 0 && x < WIN_W)
            game->z_buffer[x] = game->raycast.perpwalldist;
		if (game->raycast.side == 0)
			game->raycast.wall_x = game->pos_y + \
			game->raycast.perpwalldist * game->raycast.raydiry;
		else
			game->raycast.wall_x = game->pos_x + \
			game->raycast.perpwalldist * game->raycast.raydirx;
		game->raycast.wall_x -= floor(game->raycast.wall_x);
		calculate_draw_bound(game);
		prepare_texture_params(game);
		draw_column(game, x, game->raycast.drawstart, game->raycast.drawend);
		x++;
	}
	draw_frame_continue(game);
}
