/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_playable_map.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aline-arthur <aline-arthur@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:39:38 by nade-lim          #+#    #+#             */
/*   Updated: 2025/11/15 12:22:50 by aline-arthu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**copy_map_dup(t_game *game)
{
	int		y;
	char	**copy;

	y = 0;
	copy = ft_calloc(game->map->height + 1, sizeof(char *));
	if (!copy)
		exit_with_error("Memory error", game, NULL);
	while (y < game->map->height)
	{
		copy[y] = ft_strdup(game->map->map[y]);
		if (!copy[y])
			exit_with_error("Memory error", game, NULL);
		y++;
	}
	return (copy);
}

static int	is_walkable(char c)
{
	if (c == '0' || c == 'B' || c == 'C')
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

static void	flood_fill_playable(char **map, int y, int x, t_lim *lim)
{
	if (y < 0 || x < 0 || y >= lim->h)
		return ;
	if (x >= (int)ft_strlen(map[y]))
		return ;
	if (!is_walkable(map[y][x]))
		return ;
	map[y][x] = 'V';
	flood_fill_playable(map, y + 1, x, lim);
	flood_fill_playable(map, y - 1, x, lim);
	flood_fill_playable(map, y, x + 1, lim);
	flood_fill_playable(map, y, x - 1, lim);
}

void	check_playable_map(t_game *game)
{
	char	**copy;
	t_lim	lim;
	int		y;
	int		x;

	lim.h = game->map->height;
	lim.w = game->map->width;
	copy = copy_map_dup(game);
	flood_fill_playable(copy, game->map->player_y, game->map->player_x, &lim);
	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < (int)ft_strlen(copy[y]))
		{
			if (copy[y][x] == 'B' || copy[y][x] == 'C')
				exit_with_error("Map not playable", game, NULL);
			x++;
		}
		y++;
	}
	free_arr(&copy);
}
