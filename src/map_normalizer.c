/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_normalizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aline-arthur <aline-arthur@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 22:37:46 by aarie-c2@c1       #+#    #+#             */
/*   Updated: 2025/11/15 12:21:55 by aline-arthu      ###   ########.fr       */
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

static void	pad_rows_with_walls(t_game *game)
{
	int		y;
	int		len;
	char	*new_row;

	y = 0;
	while (y < game->map->height)
	{
		len = ft_strlen(game->map->map[y]);
		if (len < game->map->width)
		{
			new_row = alloc_and_copy_row(game->map->map[y], \
				len, game->map->width);
			if (!new_row)
				exit_with_error("Row alloc failed", game, NULL);
			free(game->map->map[y]);
			game->map->map[y] = new_row;
		}
		y++;
	}
}

void	normalize_map(t_game *game)
{
	pad_rows_with_walls(game);
	replace_spaces_with_walls(game->map);
}
