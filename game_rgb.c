/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_rgb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:52:12 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/10/20 09:53:31 by aarie-c2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int rgb_to_int(int rgb[3])
{
    int r = rgb[0];
    int g = rgb[1];
    int b = rgb[2];

    return (r << 16) | (g << 8) | b;
}

static void my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
    char    *dst;

    if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
        return ;
    dst = game->addr + (y * game->line_len + x * (game->bpp / 8));
    *(unsigned int*)dst = color;
}

void	draw_column(t_game *game, int x, int drawStart, int drawEnd)
{
	int	y;

	y = 0;
	while (y < drawStart)
	{
		my_mlx_pixel_put(game, x, y, rgb_to_int(game->map->color_ceiling));
		y++;
	}
	while (y <= drawEnd)
	{
		my_mlx_pixel_put(game, x, y, rgb_to_int(game->map->color_floor)); // For now solid wall color
		y++;
	}
	while (y < WIN_H)
	{
		my_mlx_pixel_put(game, x, y, rgb_to_int(game->map->color_floor));
		y++;
	}
}
