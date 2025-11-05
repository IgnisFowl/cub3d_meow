/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cats_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aline-arthur <aline-arthur@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:28:32 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/11/04 22:46:11 by aline-arthu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_cat_counter(t_game *g, int text_y)
{
	char	*num;
	int		collected;

	draw_cat_icon(g);
	collected = get_collected_cats(g);
	num = ft_itoa(collected);
	mlx_string_put(g->mlx, g->win, 165, text_y, 0xFFD700, "x");
	mlx_string_put(g->mlx, g->win, 178, text_y, 0xFFD700, num);
	free(num);
}

static void	draw_total_cats(t_game *g, int text_y)
{
	char	*num;

	mlx_string_put(g->mlx, g->win, 195, text_y, 0x888888, "/");
	num = ft_itoa(g->cats.num_cats);
	mlx_string_put(g->mlx, g->win, 205, text_y, 0x888888, num);
	free(num);
}

static void	draw_snack_counter(t_game *g, int text_y)
{
	char	*num;

	num = ft_itoa(g->cats.snacks_inv);
	mlx_string_put(g->mlx, g->win, 85, text_y, 0xFFFFFF, "x");
	mlx_string_put(g->mlx, g->win, 98, text_y, 0xFFFFFF, num);
	free(num);
}

void	draw_hud(t_game *g)
{
	int	text_y;

	draw_hud_box(g);
	draw_snack_icon(g);
	text_y = WIN_H - 120;
	draw_snack_counter(g, text_y);
	draw_cat_counter(g, text_y);
	draw_total_cats(g, text_y);
}
