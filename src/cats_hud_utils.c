/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cats_hud_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nade-lim <nade-lim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 14:39:47 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/11/13 15:34:09 by nade-lim         ###   ########.fr       */
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
	pixel = g->cats.snack_texture.addr + (tex_y * \
		g->cats.snack_texture.line_len + tex_x * \
		(g->cats.snack_texture.bpp / 8));
	color = *(unsigned int *)pixel;
	return (color);
}

int	get_cat_tex_pixel(t_game *g, int tex_x, int tex_y)
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

void	draw_cat_pixel(t_game *g, int x, int y)
{
	int	tex_x;
	int	tex_y;
	int	color;
	int	hud_y;

	tex_x = (x * g->cats.cat_textures[0][0].width) / 45;
	tex_y = (y * g->cats.cat_textures[0][0].height) / 45;
	color = get_cat_tex_pixel(g, tex_x, tex_y);
	hud_y = WIN_H - 145;
	if (color != -1 && (color & 0x00FFFFFF) != 0)
		draw_hud_pixel(g, 115 + x, hud_y + y, color);
}

void	draw_snack_pixel(t_game *g, int x, int y)
{
	int	tex_x;
	int	tex_y;
	int	color;
	int	hud_y;

	tex_x = (x * g->cats.snack_texture.width) / 40;
	tex_y = (y * g->cats.snack_texture.height) / 40;
	color = get_snack_tex_pixel(g, tex_x, tex_y);
	hud_y = WIN_H - 145;
	if (color != -1 && (color & 0x00FFFFFF) != 0)
		draw_hud_pixel(g, 33 + x, hud_y + y, color);
}
