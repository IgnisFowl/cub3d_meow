/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cats_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:32:57 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/11/01 13:46:28 by aarie-c2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_sprite_stripe(t_game *g, t_spr_calc *c, t_texture *tex, int stripe)
{
	int	y;
	int	tex_x;
	int	tex_y;
	int	color;

    if (stripe < 0 || stripe >= WIN_W)
		return ;
	if (c->trans_y >= g->z_buffer[stripe])
		return ;
	tex_x = (int)((stripe - c->draw_start_x) * tex->width / c->width);
	y = c->draw_start_y;
	while (y < c->draw_end_y)
	{
		tex_y = ((y - WIN_H / 2 + c->height / 2) * tex->height) / c->height;
		color = get_tex_pixel(tex, tex_x, tex_y);
		if (color != -1)
			put_sprite_pixel(g, stripe, y, color);
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
