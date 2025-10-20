/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:30:35 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/10/20 09:08:32 by aarie-c2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_game *game)
{
	if (!game)
		return (0);
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
	ft_printf("Game closed cleanly\n");
	exit(0);
	return (0);
}

void	free_arr(char ***arr)
{
	int i;

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
