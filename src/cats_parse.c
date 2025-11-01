/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cats_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:00:46 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/11/01 15:17:35 by aarie-c2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	add_cat(t_game *g, int *idx, int x, int y)
{
	g->cats.cats[*idx].x = (double)x + 0.5;
	g->cats.cats[*idx].y = (double)y + 0.5;
	g->cats.cats[*idx].type = *idx % 3;
	g->cats.cats[*idx].active = 1;
	g->cats.cats[*idx].frame = 0;
	g->cats.cats[*idx].dist = 0.0;
	(*idx)++;
}

static void	add_snack(t_game *g, int *idx, int x, int y)
{
	g->cats.snacks[*idx].x = (double)x + 0.5;
	g->cats.snacks[*idx].y = (double)y + 0.5;
	g->cats.snacks[*idx].type = 0;
	g->cats.snacks[*idx].active = 1;
	g->cats.snacks[*idx].frame = 0;
	g->cats.snacks[*idx].dist = 0.0;
	(*idx)++;
}

static void	parse_cats_loop(t_game *g, int *cat_i, int *snack_i)
{
	int	y;
	int	x;

	y = 0;
	while (y < g->map->height)
	{
		x = 0;
		while (g->map->map[y][x])
		{
			if (g->map->map[y][x] == 'C')
				add_cat(g, cat_i, x, y);
			else if (g->map->map[y][x] == 'B')
				add_snack(g, snack_i, x, y);
			x++;
		}
		y++;
	}
}

void	parse_cats(t_game *game)
{
	int	cat_idx;
	int	snack_idx;

	cat_idx = 0;
	snack_idx = 0;
	parse_cats_loop(game, &cat_idx, &snack_idx);
}

void	clear_cats_from_map(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (game->map->map[y][x])
		{
			if (game->map->map[y][x] == 'C')
				game->map->map[y][x] = '0';
			else if (game->map->map[y][x] == 'B')
				game->map->map[y][x] = '0';
			x++;
		}
		y++;
	}
}
