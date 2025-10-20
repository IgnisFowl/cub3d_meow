/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_final.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:45:46 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/10/20 08:54:23 by aarie-c2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	count_map_dimensions(t_map *map, char **map_lines)
{
	int	i;
	int	len;

	i = 0;
	while (map_lines[i])
	{
		len = ft_strlen(map_lines[i]);
		if (len > map->width)
			map->width = len;
		i++;
	}
	map->height = i;
}

static void	copy_map_lines(t_map *map, char **map_lines)
{
	int	y;

	map->map = malloc(sizeof(char *) * (map->height + 1));
	if (!map->map)
		exit_with_error("Map alloc failed", map, NULL, NULL);
	y = 0;
	while (y < map->height)
	{
		map->map[y] = ft_strdup(map_lines[y]);
		if (!map->map[y])
			exit_with_error("Line strdup failed", map, NULL, NULL);
		y++;
	}
	map->map[y] = NULL;
}
	
static void	find_player_start(t_map *map)
{
	int	y;
	int	x;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < (int)ft_strlen(map->map[y]))
		{
			if (ft_strchr("NSEW", map->map[y][x]))
			{
				map->player_x = x;
				map->player_y = y;
				map->player_dir = map->map[y][x];
				map->map[y][x] = '0';
				return ;
			}
		}
	}
}

void	finalize_map(t_map *map, char **map_lines)
{
	count_map_dimensions(map, map_lines);
	copy_map_lines(map, map_lines);
	find_player_start(map);
}
