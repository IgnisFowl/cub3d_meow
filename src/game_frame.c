/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aline-arthur <aline-arthur@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:28:04 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/11/04 23:28:12 by aline-arthu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    draw_start_screen(t_game *g)
{
    if (!g || !g->mlx || !g->win || !g->start_img)
        return ;
    mlx_put_image_to_window(g->mlx, g->win, g->start_img, 0, 0);
}

static void	draw_frame_continue(t_game *game)
{
	if (game->game_started == 0)
    {
        draw_start_screen(game);
        return ;
    }
	render_sprites(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	minimap_present(game, 16, 90);
	draw_hud(game);
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
