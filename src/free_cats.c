/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cats.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:46:45 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/11/01 15:29:28 by aarie-c2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_cat_textures(t_game *game)
{
	int	type;
	int	frame;

	type = 0;
	while (type < 3)
	{
		frame = 0;
		while (frame < 3)
		{
			if (game->cats.cat_textures[type][frame].img)
				mlx_destroy_image(game->mlx,
					game->cats.cat_textures[type][frame].img);
			frame++;
		}
		type++;
	}
	if (game->cats.snack_texture.img)
		mlx_destroy_image(game->mlx, game->cats.snack_texture.img);
}

void	free_cats(t_game *game)
{
	if (game->cats.cats)
	{
		free(game->cats.cats);
		game->cats.cats = NULL;
	}
	if (game->cats.snacks)
	{
		free(game->cats.snacks);
		game->cats.snacks = NULL;
	}
	free_cat_textures(game);
}
