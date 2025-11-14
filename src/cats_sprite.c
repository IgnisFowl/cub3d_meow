/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cats_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nade-lim <nade-lim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:32:57 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/11/13 15:31:31 by nade-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_sprite_stripe(t_game *g, t_spr_calc *c, \
	t_texture *tex, int stripe)
{
	int	y;
	int	tex_x;
	int	tex_y;
	int	color;

	if (stripe < 0 || stripe >= WIN_W || c->trans_y <= 0 || \
		c->trans_y > g->z_buffer[stripe])
		return ;
	tex_x = ((stripe - (-c->width / 2 + c->screen_x)) * tex->width) / c->width;
	if (tex_x < 0)
		tex_x = 0;
	else if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	y = c->draw_start_y;
	while (y < c->draw_end_y)
	{
		tex_y = ((y - c->draw_start_y) * tex->height) / c->height;
		if (tex_y >= 0 && tex_y < tex->height)
		{
			color = get_tex_pixel(tex, tex_x, tex_y);
			if (color != -1)
				put_sprite_pixel(g, stripe, y, color);
		}
		y++;
	}
}

void	draw_one_sprite(t_game *g, t_sprite *s, t_texture *tex)
{
	t_spr_calc	calc;
	int			stripe;

	init_sprite_calc(g, s, &calc);
	if (calc.trans_y <= 0)
		return ;
	calc_sprite_screen(&calc);
	calc_sprite_bounds(&calc);
	stripe = calc.draw_start_x;
	while (stripe < calc.draw_end_x)
	{
		draw_sprite_stripe(g, &calc, tex, stripe);
		stripe++;
	}
}
