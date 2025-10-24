/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2@c1r4p1.42sp.org.br <aarie-c2@c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 11:44:52 by aarie-c2@c1       #+#    #+#             */
/*   Updated: 2025/10/24 16:46:13 by aarie-c2@c1      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	c_str_len(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

static int	in_bounds_px(t_game *g, int x, int y)
{
	if (!g || !g->imgt)
		return (0);
	if (x < 0 || y < 0)
		return (0);
	if (x >= g->imgt->w || y >= g->imgt->h)
		return (0);
	return (1);
}

void	minimap_put_px(t_game *g, int x, int y, int color)
{
	int				bytes_pp;
	int				offset;
	char			*dst;
	unsigned int	*udst;

	if (!g || !g->imgt || !g->imgt->addr)
		return ;
	if (!in_bounds_px(g, x, y))
		return ;
	bytes_pp = g->imgt->bpp / 8;
	if (bytes_pp <= 0)
		return ;
	offset = y * g->imgt->line_len + x * bytes_pp;
	dst = g->imgt->addr + offset;
	udst = (unsigned int *)dst;
	*udst = (unsigned int)color;
}
