/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cats_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 12:53:40 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/11/01 15:16:34 by aarie-c2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_map_char(t_game *game, char c)
{
	int	count;
	int	y;
	int	x;

	count = 0;
	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (game->map->map[y][x])
		{
			if (game->map->map[y][x] == c)
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static void	init_cats_struct(t_game *game)
{
	game->cats.num_cats = count_map_char(game, 'C');
	game->cats.num_snacks = count_map_char(game, 'B') + 1;
	game->cats.snacks_inv = 0;
	game->cats.anim_time = 0.0;
}

static void    alloc_cats_array(t_game *game)
{
	int	size_c;
	int	size_s;

	size_c = sizeof(t_sprite) * game->cats.num_cats;
	size_s = sizeof(t_sprite) * game->cats.num_snacks;
	game->cats.cats = malloc(size_c);
	game->cats.snacks = malloc(size_s);
	if (!game->cats.cats || !game->cats.snacks)
		return ;
	ft_memset(game->cats.cats, 0, size_c);
	ft_memset(game->cats.snacks, 0, size_s);
}

void	init_cats(t_game *game)
{
	init_cats_struct(game);
	alloc_cats_array(game);
	parse_cats(game);
	clear_cats_from_map(game);
	load_cats_textures(game);
}
