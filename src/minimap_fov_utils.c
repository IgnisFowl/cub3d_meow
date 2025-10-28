/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_fov_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2@c1r4p1.42sp.org.br <aarie-c2@c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:54:39 by aarie-c2@c1       #+#    #+#             */
/*   Updated: 2025/10/24 18:29:31 by aarie-c2@c1      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_fov_pos(t_game *g, t_fov *f)
{
	f->player_px = (int)(g->pos_x * TILE_SIZE) + TILE_SIZE / 2;
	f->player_py = (int)(g->pos_y * TILE_SIZE) + TILE_SIZE / 2;
}

void	calc_fov_edges(t_game *g, t_fov *f)
{
	double	len;

	len = 2 * TILE_SIZE;

	f->end_left_x = f->player_px + (int)((g->dir_x + g->plane_x) * len);
	f->end_left_y = f->player_py + (int)((g->dir_y + g->plane_y) * len);
	f->end_right_x = f->player_px + (int)((g->dir_x - g->plane_x) * len);
	f->end_right_y = f->player_py + (int)((g->dir_y - g->plane_y) * len);
}

void fov_to_triangle(t_fov *f, t_triangle *t)
{
	t->x0 = f->player_px;
	t->y0 = f->player_py;
	t->x1 = f->end_left_x;
	t->y1 = f->end_left_y;
	t->x2 = f->end_right_x;
	t->y2 = f->end_right_y;
}

void tri_bounds(t_triangle *t, t_tri_bounds *b)
{
	b->min_x = b->max_x = t->x0;
	b->min_y = b->max_y = t->y0;
	if (t->x1 < b->min_x)
		b->min_x = t->x1;
	if (t->x2 < b->min_x)
		b->min_x = t->x2;
	if (t->x1 > b->max_x)
		b->max_x = t->x1;
	if (t->x2 > b->max_x)
		b->max_x = t->x2;
	if (t->y1 < b->min_y)
		b->min_y = t->y1;
	if (t->y2 < b->min_y)
		b->min_y = t->y2;
	if (t->y1 > b->max_y)
		b->max_y = t->y1;
	if (t->y2 > b->max_y)
		b->max_y = t->y2;
}

int point_in_tri(t_triangle *t, int x, int y)
{
	int 	d;
	float 	a;
	float	b;
	float	c;

	d = (t->y1 - t->y2) * (t->x0 - t->x2) + (t->x2 - t->x1) * (t->y0 - t->y2);
	if (!d)
		return (0);
	a = ((t->y1 - t->y2) * (x - t->x2) + (t->x2 - t->x1) * (y - t->y2)) / (float)d;
	b = ((t->y2 - t->y0) * (x - t->x2) + (t->x0 - t->x2) * (y - t->y2)) / (float)d;
	c = 1 - a - b;
	return (a >= 0 && b >= 0 && c >= 0);
}
