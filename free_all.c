/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:30:35 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/10/17 12:26:30 by aarie-c2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
