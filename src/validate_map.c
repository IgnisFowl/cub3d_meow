/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nade-lim <nade-lim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:09:44 by nade-lim          #+#    #+#             */
/*   Updated: 2025/11/06 16:59:23 by nade-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_tile(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == 'C' || c == 'B' || c == ' ');
}

static void	clean_line(char *line)
{
	int	i;

	if (!line)
		return ;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\r' || line[i] == '\t')
			line[i] = ' ';
		else if (line[i] == '\n')
		{
			line[i] = '\0';
			return ;
		}
		i++;
	}
}

static void	check_invalid_chars(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		clean_line(map->map[y]);
		x = 0;
		while (map->map[y][x])
		{
			if (!is_valid_tile(map->map[y][x]))
				exit_with_error("Invalid character in map", map, NULL, NULL);
			x++;
		}
		y++;
	}
}

static void	check_single_player(t_map *map)
{
	int	count;
	int	y;
	int	x;

	count = 0;
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < (int)ft_strlen(map->map[y]))
			if (ft_strchr("NSEW", map->map[y][x]))
				count++;
	}
	if (count == 0)
		exit_with_error("Map must contain a player", map, NULL, NULL);
	if (count > 1)
		exit_with_error("Map must contain exactly one player", map, NULL, NULL);
}

void	validate_map(t_map *map)
{
	check_invalid_chars(map);
	check_single_player(map);
	check_walls_closed(map);
}
