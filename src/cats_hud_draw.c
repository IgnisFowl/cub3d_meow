/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cats_hud_draw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aline-arthur <aline-arthur@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 22:26:31 by aline-arthu       #+#    #+#             */
/*   Updated: 2025/11/04 22:43:56 by aline-arthu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_hud_box(t_game *g)
{
	int x;
	int y;
	int start_y;
	int end_y;

	start_y = WIN_H - 160;
	end_y = WIN_H - 90;
	y = start_y;
	while (y < end_y)
	{
		x = 20;
		while (x < 220)
		{
			draw_hud_pixel(g, x, y, 0x333333);
			x++;
		}
		y++;
	}
}

void	draw_cat_icon(t_game *g)
{
	int	x;
	int	y;

	y = 0;
	while (y < 45)
	{
		x = 0;
		while (x < 45)
		{
			draw_cat_pixel(g, x, y);
			x++;
		}
		y++;
	}
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
