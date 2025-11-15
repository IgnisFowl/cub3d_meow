/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_final.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aline-arthur <aline-arthur@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:45:46 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/11/15 13:52:03 by aline-arthu      ###   ########.fr       */
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

static void	copy_map_lines(t_game *game, char **map_lines)
{
	int	y;

	game->map->map = malloc(sizeof(char *) * (game->map->height + 1));
	if (!game->map->map)
		exit_with_error("Map alloc failed", game, NULL);
	y = 0;
	while (y < game->map->height)
	{
		game->map->map[y] = ft_strdup(map_lines[y]);
		if (!game->map->map[y])
			exit_with_error("Line strdup failed", game, NULL);
		y++;
	}
	game->map->map[y] = NULL;
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

int	is_inside_map(t_map *map, int x, int y)
{
	int	row_len;

	if (y < 0 || y >= map->height)
		return (0);
	row_len = ft_strlen(map->map[y]);
	if (x < 0 || x >= row_len)
		return (0);
	return (1);
}

void	finalize_map(t_game *game, char **map_lines)
{
	count_map_dimensions(game->map, map_lines);
	copy_map_lines(game, map_lines);
	validate_map(game, map_lines);
	find_player_start(game->map);
	if (!check_playable_map(game))
	{
		free_arr(&map_lines);
		exit_with_error("Map not playable!", game, NULL);
	}
	normalize_map(game);
}
