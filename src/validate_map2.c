/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aline-arthur <aline-arthur@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:57:41 by nade-lim          #+#    #+#             */
/*   Updated: 2025/11/08 17:08:18 by aline-arthu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_walls_closed(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] == '0' && (
				y == 0 || x == 0 || y == map->height - 1
				|| x == (int)ft_strlen(map->map[y]) - 1
				|| map->map[y - 1][x] == ' '
				|| map->map[y + 1][x] == ' '
				|| map->map[y][x - 1] == ' '
				|| map->map[y][x + 1] == ' '))
				exit_with_error("Map not closed", map, NULL, NULL);
			x++;
		}
		y++;
	}
}

void	validate_cub_extension(char *filename, t_map *map)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5)
		exit_with_error("Invalid file name", map, NULL, NULL);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		exit_with_error("Invalid file extension (expected .cub)" \
			, map, NULL, NULL);
}

void	check_required_colors(t_map *map)
{
	int	floor_defined;
	int	ceiling_defined;

	floor_defined = (map->color_floor[0] != -1
			|| map->color_floor[1] != -1
			|| map->color_floor[2] != -1);
	ceiling_defined = (map->color_ceiling[0] != -1
			|| map->color_ceiling[1] != -1
			|| map->color_ceiling[2] != -1);
	if (!floor_defined || !ceiling_defined)
		exit_with_error("Missing floor or ceiling color", map, NULL, NULL);
}

static int is_readable(const char *p)
{
    int fd;

    if (!p || access(p, R_OK) != 0)
        return (0);
    fd = open(p, O_RDONLY);
    if (fd < 0)
        return (0);
    close(fd);
    return (1);
}

int	validate_config(t_map *map)
{
	if (!map)
		return (0);
	if (!is_readable(map->texture_north)
		|| !is_readable(map->texture_south)
		|| !is_readable(map->texture_west)
		|| !is_readable(map->texture_east))
		return (0);
	check_required_colors(map);
	return (1);
}
