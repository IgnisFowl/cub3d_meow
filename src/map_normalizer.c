/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_normalizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2@c1r4p1.42sp.org.br <aarie-c2@c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 22:37:46 by aarie-c2@c1       #+#    #+#             */
/*   Updated: 2025/10/24 11:39:26 by aarie-c2@c1      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	replace_spaces_with_walls(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == ' ' || map->map[y][x] == '\0')
				map->map[y][x] = '1';
			x++;
		}
		y++;
	}
}

static char	*alloc_and_copy_row(char *old, int len, int width)
{
	char	*new_row;
	int		i;

	new_row = malloc(sizeof(char) * (width + 1));
	if (!new_row)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (old[i] == '\n')
			break ;
		new_row[i] = old[i];
		i++;
	}
	while (i < width)
	{
		new_row[i] = '1';
		i++;
	}
	new_row[width] = '\0';
	return (new_row);
}

static void	pad_rows_with_walls(t_map *map)
{
	int		y;
	int		len;
	char	*new_row;

	y = 0;
	while (y < map->height)
	{
		len = ft_strlen(map->map[y]);
		if (len < map->width)
		{
			new_row = alloc_and_copy_row(map->map[y], len, map->width);
			if (!new_row)
				exit_with_error("Row alloc failed", map, NULL, NULL);
			free(map->map[y]);
			map->map[y] = new_row;
		}
		y++;
	}
}

void	normalize_map(t_map *map)
{
	pad_rows_with_walls(map);
	replace_spaces_with_walls(map);
}
