/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cats_render_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:41:11 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/11/01 13:41:56 by aarie-c2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calc_sprite_distance(t_game *g, t_sprite *s)
{
	double	dx;
	double	dy;

	dx = g->pos_x - s->x;
	dy = g->pos_y - s->y;
	s->dist = dx * dx + dy * dy;
}

void	update_all_distances(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->cats.num_cats)
	{
		if (game->cats.cats[i].active)
			calc_sprite_distance(game, &game->cats.cats[i]);
		i++;
	}
	i = 0;
	while (i < game->cats.num_snacks)
	{
		if (game->cats.snacks[i].active)
			calc_sprite_distance(game, &game->cats.snacks[i]);
		i++;
	}
}

static void	swap_sprites(t_sprite *a, t_sprite *b)
{
	t_sprite	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static void	sort_sprites_array(t_sprite *arr, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (arr[j].dist < arr[j + 1].dist)
				swap_sprites(&arr[j], &arr[j + 1]);
			j++;
		}
		i++;
	}
}

void	sort_all_sprites(t_game *game)
{
	sort_sprites_array(game->cats.cats, game->cats.num_cats);
	sort_sprites_array(game->cats.snacks, game->cats.num_snacks);
}
