/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cats.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aline-arthur <aline-arthur@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:46:45 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/11/04 13:33:37 by aline-arthu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void    free_fireworks(t_game *game)
{
	int	fw;
	int	frame;

	fw = 0;
	while (fw < 3)
	{
		frame = 0;
		while (frame < 7)
		{
			if (game->fireworks[fw].textures[frame].img)
				mlx_destroy_image(game->mlx, 
					game->fireworks[fw].textures[frame].img);
			frame++;
		}
		fw++;
	}
}

static void	free_cat_textures(t_game *game)
{
	int	type;
	int	frame;

	type = 0;
	while (type < 9)
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

static void	free_win_screen(t_game *game)
{
	if (game->win_screen.img)
	{
		mlx_destroy_image(game->mlx, game->win_screen.img);
		game->win_screen.img = NULL;
	}
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
	free_fireworks(game);
	free_win_screen(game);
}
