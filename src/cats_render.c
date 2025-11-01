/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cats_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:33:33 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/11/01 13:37:58 by aarie-c2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_texture	*get_cat_texture(t_game *g, t_sprite *cat)
{
	return (&g->cats.cat_textures[cat->type][cat->frame]);
}

static void	render_all_cats(t_game *game)
{
	int			i;
	t_texture	*tex;

	update_all_distances(game);
	sort_all_sprites(game);
	i = 0;
	while (i < game->cats.num_cats)
	{
		if (game->cats.cats[i].active)
		{
			tex = get_cat_texture(game, &game->cats.cats[i]);
			draw_one_sprite(game, &game->cats.cats[i], tex);
		}
		i++;
	}
}

static void	render_all_snacks(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->cats.num_snacks)
	{
		if (game->cats.snacks[i].active)
			draw_one_sprite(game, &game->cats.snacks[i],
				&game->cats.snack_texture);
		i++;
	}
}

void	render_sprites(t_game *game)
{
	render_all_cats(game);
	render_all_snacks(game);
}
