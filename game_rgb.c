/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_rgb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2@c1r4p1.42sp.org.br <aarie-c2@c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:52:12 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/10/21 21:10:55 by aarie-c2@c1      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	rgb_to_int(int rgb[3])
{
	int	r;
	int	g;
	int	b;

	r = rgb[0];
	g = rgb[1];
	b = rgb[2];
	return ((r << 16) | (g << 8) | b);
}

static void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	dst = game->addr + (y * game->line_len + x * (game->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_column(t_game *game, int x, int drawStart, int drawEnd)
{
	int	y;

	if (drawStart > drawEnd)
		return ;
	y = 0;
	while (y < drawStart)
	{
		my_mlx_pixel_put(game, x, y, rgb_to_int(game->map->color_ceiling));
		y++;
	}
	while (y <= drawEnd)
	{
		my_mlx_pixel_put(game, x, y, 0x888888); // solid gray wall color
		y++;
	}
	while (y < WIN_H)
	{
		my_mlx_pixel_put(game, x, y, rgb_to_int(game->map->color_floor));
		y++;
	}	
}
