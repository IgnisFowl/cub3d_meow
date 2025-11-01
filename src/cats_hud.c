/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cats_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:28:32 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/11/01 14:39:56 by aarie-c2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_hud_box(t_game *g)
{
	int	x;
	int	y;

	y = WIN_H - 64;
	while (y < WIN_H - 10)
	{
		x = 10;
		while (x < 100)
		{
			draw_hud_pixel(g, x, y, 0x333333);
			x++;
		}
		y++;
	}
}

void	draw_snack_pixel(t_game *g, int x, int y)
{
	int	tex_x;
	int	tex_y;
	int	color;

	tex_x = (x * g->cats.snack_texture.width) / 40;
	tex_y = (y * g->cats.snack_texture.height) / 40;
	color = get_snack_tex_pixel(g, tex_x, tex_y);
	if (color != -1 && (color & 0x00FFFFFF) != 0)
		draw_hud_pixel(g, 15 + x, WIN_H - 59 + y, color);
}

void	draw_snack_icon(t_game *g)
{
	int	x;
	int	y;

	draw_hud_box(g);
	y = 0;
	while (y < 40)
	{
		x = 0;
		while (x < 40)
		{
			draw_snack_pixel(g, x, y);
			x++;
		}
		y++;
	}
}

void	draw_snack_text(t_game *game)
{
	char	*num;

	num = ft_itoa(game->cats.snacks_inv);
	mlx_string_put(game->mlx, game->win, 65, WIN_H - 35,
		0xFFFFFF, "x");
	mlx_string_put(game->mlx, game->win, 78, WIN_H - 35,
		0xFFFFFF, num);
	free(num);
}
