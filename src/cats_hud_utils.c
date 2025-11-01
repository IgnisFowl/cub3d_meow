/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cats_hud_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 14:39:47 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/11/01 14:40:05 by aarie-c2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_hud_pixel(t_game *g, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	dst = g->addr + (y * g->line_len + x * (g->bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_snack_tex_pixel(t_game *g, int tex_x, int tex_y)
{
	char	*pixel;
	int		color;

	if (tex_x < 0 || tex_x >= g->cats.snack_texture.width)
		return (-1);
	if (tex_y < 0 || tex_y >= g->cats.snack_texture.height)
		return (-1);
	pixel = g->cats.snack_texture.addr + (tex_y * 
		g->cats.snack_texture.line_len + tex_x * 
		(g->cats.snack_texture.bpp / 8));
	color = *(unsigned int *)pixel;
	return (color);
}
