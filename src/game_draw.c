/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2@c1r4p1.42sp.org.br <aarie-c2@c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:52:12 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/10/21 21:48:03 by aarie-c2@c1      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_texture	*get_current_texture(t_game *game)
{
	if (game->raycast.side == 0)
	{
		if (game->raycast.raydirx > 0)
			return (&game->texture_west);
		else
			return (&game->texture_east);
	}
	else
	{
		if (game->raycast.raydiry > 0)
			return (&game->texture_north);
		else
			return (&game->texture_south);
	}
}

static void	draw_ceiling(t_game *game, int x, int drawstart)
{
	int	y;

	y = 0;
	while (y < drawstart)
	{
		my_mlx_pixel_put(game, x, y, rgb_to_int(game->map->color_ceiling));
		y++;
	}
}

static void	draw_wall_slice(t_game *game, int x, int drawStart, int drawEnd)
{
	int			y;
	int			tex_y;
	int			color;
	t_texture	*texture;

	texture = get_current_texture(game);
	y = drawStart;
	while (y <= drawEnd)
	{
		tex_y = (int)game->raycast.tex_pos & (texture->height - 1);
		game->raycast.tex_pos += game->raycast.step;

		color = *(int *)(texture->addr + (tex_y * \
			texture->line_len + game->raycast.tex_x * (texture->bpp / 8)));
		my_mlx_pixel_put(game, x, y, color);
		y++;
	}
}

static void	draw_floor(t_game *game, int x, int drawEnd)
{
	int	y;

	y = drawEnd + 1;
	while (y < WIN_H)
	{
		my_mlx_pixel_put(game, x, y, rgb_to_int(game->map->color_floor));
		y++;
	}
}

void	draw_column(t_game *game, int x, int drawStart, int drawEnd)
{
	if (drawStart > drawEnd)
		return ;

	draw_ceiling(game, x, drawStart);
	draw_wall_slice(game, x, drawStart, drawEnd);
	draw_floor(game, x, drawEnd);
}
