/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_fov.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2@c1r4p1.42sp.org.br <aarie-c2@c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:54:39 by aarie-c2@c1       #+#    #+#             */
/*   Updated: 2025/10/24 18:29:31 by aarie-c2@c1      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_tri_row(t_game *g, t_triangle *t, t_tri_bounds *b, int y)
{
	int	x;

	x = b->min_x;
	while (x <= b->max_x)
	{
		if (point_in_tri(t, x, y))
			minimap_put_px(g, x, y, COLOR_FOV_TRIANGLE);
		x++;
	}
}

static void	minimap_draw_tri(t_game *g, t_triangle *t, t_tri_bounds *b)
{
	int y;

	y = b->min_y;
	while (y <= b->max_y)
	{
		fill_tri_row(g, t, b, y);
		y++;
	}
}

void	draw_minimap_fov(t_game *g)
{
	t_fov			fov;
	t_triangle		tri;
	t_tri_bounds	b;

	if (!g || !g->imgt || !g->imgt->addr)
		return ;
	init_fov_pos(g, &fov);
	calc_fov_edges(g, &fov);
	fov_to_triangle(&fov, &tri);
	tri_bounds(&tri, &b);
	minimap_draw_tri(g, &tri, &b);
}
