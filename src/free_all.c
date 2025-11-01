/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:30:35 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/11/01 16:08:48 by aarie-c2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_arr(char ***arr)
{
	int	i;

	if (!arr || !*arr)
		return ;
	i = 0;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->texture_north)
		free(map->texture_north);
	if (map->texture_south)
		free(map->texture_south);
	if (map->texture_west)
		free(map->texture_west);
	if (map->texture_east)
		free(map->texture_east);
	if (map->map)
		free_arr(&map->map);
	free(map);
}

void	free_textures(t_game *game)
{
	if (game->texture_north.img)
		mlx_destroy_image(game->mlx, game->texture_north.img);
	if (game->texture_south.img)
		mlx_destroy_image(game->mlx, game->texture_south.img);
	if (game->texture_west.img)
		mlx_destroy_image(game->mlx, game->texture_west.img);
	if (game->texture_east.img)
		mlx_destroy_image(game->mlx, game->texture_east.img);
}

void	free_imgt(t_game *game)
{
	if (game->imgt)
	{
		if (game->imgt->img && game->mlx)
			mlx_destroy_image(game->mlx, game->imgt->img);
		free(game->imgt);
		game->imgt = NULL;
	}
}

int	close_window(t_game *game)
{
	if (!game)
		return (0);
	free_textures(game);
	free_cats(game);
	if (game->z_buffer)
	{
		free(game->z_buffer);
		game->z_buffer = NULL;
	}
	if (game->map)
		free_map(game->map);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->imgt)
		free_imgt(game);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free(game);
	exit(0);
	return (0);
}
