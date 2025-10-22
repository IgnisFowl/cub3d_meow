/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2@c1r4p1.42sp.org.br <aarie-c2@c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:30:35 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/10/21 21:57:57 by aarie-c2@c1      ###   ########.fr       */
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
	if (map->texture_north)
	{
		free(map->texture_north);
		map->texture_north = NULL;
	}
	if (map->texture_south)
	{
		free(map->texture_south);
		map->texture_south = NULL;
	}
	if (map->texture_west)
	{
		free(map->texture_west);
		map->texture_west = NULL;
	}
	if (map->texture_east)
	{
		free(map->texture_east);
		map->texture_east = NULL;
	}
	if (map->map)
		free_arr(&map->map);
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

int	close_window(t_game *game)
{
	if (!game)
		return (0);
	free_textures(game);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->map)
		free_map(game->map);
	free(game);
	ft_printf("Game closed cleanly\n");
	exit(0);
	return (0);
}
