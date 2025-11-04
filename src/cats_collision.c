/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cats_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aline-arthur <aline-arthur@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:20:41 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/11/04 11:17:11 by aline-arthu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_near_sprite(t_game *g, t_sprite *s)
{
	double	dx;
	double	dy;
	double	dist;

	dx = g->pos_x - s->x;
	dy = g->pos_y - s->y;
	dist = sqrt(dx * dx + dy * dy);
	return (dist < 0.8);
}

static void	collect_snack(t_game *game, int idx)
{
	game->cats.snacks[idx].active = 0;
	game->cats.snacks_inv++;
}

void	check_snack_pickup(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->cats.num_snacks)
	{
		if (game->cats.snacks[i].active)
			if (is_near_sprite(game, &game->cats.snacks[i]))
				collect_snack(game, i);
		i++;
	}
}

static void	collect_cat(t_game *game, int idx)
{
	game->cats.cats[idx].active = 0;
	game->cats.snacks_inv--;
}

void	try_collect_cat(t_game *game)
{
	int	i;

	if (game->cats.snacks_inv <= 0)
		return ;
	i = 0;
	while (i < game->cats.num_cats)
	{
		if (game->cats.cats[i].active)
			if (is_near_sprite(game, &game->cats.cats[i]))
			{
				collect_cat(game, i);
				check_win_condition(game);
			}
		i++;
	}
}
