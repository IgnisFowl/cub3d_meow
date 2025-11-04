/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cats_hud_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aline-arthur <aline-arthur@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 14:39:47 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/11/04 10:34:57 by aline-arthu      ###   ########.fr       */
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

int get_cat_tex_pixel(t_game *g, int tex_x, int tex_y)
{
	t_texture	*tex;
	char		*pixel;
	int			color;

	tex = &g->cats.cat_textures[0][0];

	if (tex_x < 0 || tex_x >= tex->width)
		return (-1);
	if (tex_y < 0 || tex_y >= tex->height)
		return (-1);
	pixel = tex->addr + (tex_y * tex->line_len + tex_x * (tex->bpp / 8));
	color = *(unsigned int *)pixel;
	return (color);
}

void	draw_cat_pixel(t_game *g, int x, int y, int base_x)
{
	int	tex_x;
	int	tex_y;
	int	color;

	tex_x = (x * g->cats.cat_textures[0][0].width) / 45;
	tex_y = (y * g->cats.cat_textures[0][0].height) / 45;
	color = get_cat_tex_pixel(g, tex_x, tex_y);
	if (color != -1 && (color & 0x00FFFFFF) != 0)
		draw_hud_pixel(g, base_x + x, WIN_H - 59 + y, color);
}

void	draw_cat_icon(t_game *g, int base_x)
{
	int	x;
	int	y;

	y = 0;
	while (y < 45)
	{
		x = 0;
		while (x < 45)
		{
			draw_cat_pixel(g, x, y, base_x);
			x++;
		}
		y++;
	}
}
