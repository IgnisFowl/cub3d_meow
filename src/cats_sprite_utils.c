/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cats_sprite_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nade-lim <nade-lim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:30:31 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/11/13 15:43:45 by nade-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_sprite_calc(t_game *g, t_sprite *s, t_spr_calc *c)
{
	c->spr_x = s->x - g->pos_x;
	c->spr_y = s->y - g->pos_y;
	c->inv_det = 1.0 / (g->plane_x * g->dir_y - g->dir_x * g->plane_y);
	c->trans_x = c->inv_det * (g->dir_y * c->spr_x - g->dir_x * c->spr_y);
	c->trans_y = c->inv_det * (-g->plane_y * c->spr_x + g->plane_x * c->spr_y);
}

void	calc_sprite_screen(t_spr_calc *c)
{
	double	scale_factor;
	int		sprite_screen_height;
	int		floor_level;

	scale_factor = 1.5;
	c->screen_x = (int)((WIN_W / 2) * (1 + c->trans_x / c->trans_y));
	sprite_screen_height = abs((int)(WIN_H / (c->trans_y * scale_factor)));
	c->height = sprite_screen_height;
	c->width = sprite_screen_height;
	floor_level = WIN_H / 2 + (WIN_H / 1.5) / (c->trans_y + 0.1);
	c->draw_end_y = floor_level;
	c->draw_start_y = c->draw_end_y - c->height;
	if (c->draw_start_y < 0)
		c->draw_start_y = 0;
	if (c->draw_end_y >= WIN_H)
		c->draw_end_y = WIN_H - 1;
}

void	calc_sprite_bounds(t_spr_calc *c)
{
	c->draw_start_x = -c->width / 2 + c->screen_x;
	if (c->draw_start_x < 0)
		c->draw_start_x = 0;
	c->draw_end_x = c->width / 2 + c->screen_x;
	if (c->draw_end_x >= WIN_W)
		c->draw_end_x = WIN_W - 1;
}

int	get_tex_pixel(t_texture *tex, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (-1);
	pixel = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)pixel);
}

void	put_sprite_pixel(t_game *g, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	if ((color & 0x00FFFFFF) == 0)
		return ;
	dst = g->addr + (y * g->line_len + x * (g->bpp / 8));
	*(unsigned int *)dst = color;
}
