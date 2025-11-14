/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nade-lim <nade-lim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:54:39 by aarie-c2@c1       #+#    #+#             */
/*   Updated: 2025/11/13 15:35:27 by nade-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	minimap_img_init(t_game *g, int w, int h)
{
	void	*iptr;

	if (!g || !g->mlx || !g->imgt)
		return (0);
	if (w <= 0 || h <= 0)
		return (0);
	iptr = mlx_new_image(g->mlx, w, h);
	if (!iptr)
		return (0);
	g->imgt->img = iptr;
	g->imgt->addr = mlx_get_data_addr(g->imgt->img, \
		&g->imgt->bpp, &g->imgt->line_len, &g->imgt->endian);
	if (!g->imgt->addr)
		return (0);
	g->imgt->w = w;
	g->imgt->h = h;
	return (1);
}

int	minimap_init(t_game *g)
{
	int	w;
	int	h;
	int	max_w;
	int	max_h;

	if (!g || !g->map || !g->mlx)
		return (0);
	if (!g->imgt)
	{
		g->imgt = (t_img *)calloc(1, sizeof(t_img));
		if (!g->imgt)
			return (0);
	}
	if (TILE_SIZE <= 0 || g->map->width <= 0 || g->map->height <= 0)
		return (0);
	w = g->map->width * TILE_SIZE;
	h = g->map->height * TILE_SIZE;
	max_w = WIN_W / 3;
	max_h = WIN_H / 3;
	if (w > max_w)
		w = max_w;
	if (h > max_h)
		h = max_h;
	return (minimap_img_init(g, w, h));
}

void	draw_minimap(t_game *g)
{
	int	x;
	int	y;
	int	color;

	if (!g || !g->map || !g->imgt || !g->imgt->addr)
		return ;
	y = 0;
	while (y < g->map->height)
	{
		x = 0;
		while (x < g->map->width)
		{
			color = minimap_tile_color(g, x, y);
			minimap_draw_tile(g, x, y, color);
			x++;
		}
		y++;
	}
	g->map->player_x = (int)g->pos_x;
	g->map->player_y = (int)g->pos_y;
	draw_minimap_fov(g);
	if (g->map->player_x >= 0 && g->map->player_x < g->map->width
		&& g->map->player_y >= 0 && g->map->player_y < g->map->height)
		minimap_draw_tile(g, g->map->player_x, g->map->player_y, COLOR_PLAYER);
}

void	minimap_present(t_game *g, int sx, int sy)
{
	int	screen_x;
	int	screen_y;
	int	min_spacing;

	if (!g || !g->mlx || !g->win || !g->imgt || !g->imgt->img)
		return ;
	if (g->imgt->w <= 0 || g->imgt->h <= 0)
		return ;
	min_spacing = 20;
	if (sy < min_spacing)
		sy = min_spacing;
	if (sx < min_spacing)
		sx = min_spacing;
	screen_x = WIN_W - g->imgt->w - sx;
	screen_y = WIN_H - g->imgt->h - sy;
	if (screen_y + g->imgt->h > WIN_H)
		screen_y = WIN_H - g->imgt->h - min_spacing;
	mlx_put_image_to_window(g->mlx, g->win, g->imgt->img, \
		screen_x, screen_y);
}
