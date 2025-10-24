/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_tiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2@c1r4p1.42sp.org.br <aarie-c2@c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:25:08 by aarie-c2@c1       #+#    #+#             */
/*   Updated: 2025/10/24 16:54:50 by aarie-c2@c1      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	minimap_draw_square(t_game *g, int x, int y, int color)
{
	int	i;
	int	j;
	int	max_x;
	int	max_y;

	if ((!g || !g->imgt) || (x >= g->imgt->w || y >= g->imgt->h))
		return ;
	max_x = x + TILE_SIZE;
	if (max_x > g->imgt->w)
		max_x = g->imgt->w;
	max_y = y + TILE_SIZE;
	if (max_y > g->imgt->h)
		max_y = g->imgt->h;
	i = y;
	while (i < max_y)
	{
		j = x;
		while (j < max_x)
		{
			minimap_put_px(g, j, i, color);
			j++;
		}
		i++;
	}	
}

void	minimap_draw_tile(t_game *g, int tx, int ty, int color)
{
	int	px;
	int	py;

	if (!g || !g->imgt)
		return ;
	px = tx * TILE_SIZE;
	py = ty * TILE_SIZE;
	minimap_draw_square(g, px, py, color);
}

static int	minimap_visible_tile(t_game *g, int x, int y)
{
	int	dx;
	int	dy;
	int	r2;

	if (!g || !g->imgt)
		return (0);
	dx = x - g->map->player_x;
	dy = y - g->map->player_y;
	r2 = LIGHT_RADIUS * LIGHT_RADIUS;
	if ((dx * dx + dy * dy) <= r2)
		return (1);
	return (0);
}

int	minimap_tile_color(t_game *g, int x, int y)
{
	int		visible;
	int		rowlen;
	char	tile;

	if (!g || !g->map || !g->map->map)
		return (COLOR_FLOOR);
	if (x < 0 || y < 0 || x >= g->map->width || y >= g->map->height)
		return (COLOR_FLOOR);
	if (!g->map->map[y])
		return (COLOR_FLOOR);
	rowlen = c_str_len(g->map->map[y]);
	if (x >= rowlen)
		return (COLOR_FLOOR);
	visible = minimap_visible_tile(g, x, y);
	tile = g->map->map[y][x];
	if (visible)
	{
		if (tile == '1')
			return (COLOR_WALL);
		return (COLOR_VISIBLE);
	}
	return (COLOR_FLOOR);
}
