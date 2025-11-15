/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aline-arthur <aline-arthur@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:57:41 by nade-lim          #+#    #+#             */
/*   Updated: 2025/11/15 12:42:00 by aline-arthu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_walls_closed(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (game->map->map[y][x])
		{
			if (game->map->map[y][x] == '0' && (
				y == 0 || x == 0 || y == game->map->height - 1
				|| x == (int)ft_strlen(game->map->map[y]) - 1
				|| game->map->map[y - 1][x] == ' '
				|| game->map->map[y + 1][x] == ' '
				|| game->map->map[y][x - 1] == ' '
				|| game->map->map[y][x + 1] == ' '))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

void	validate_cub_extension(char *filename, t_game *game)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5)
		exit_with_error("Invalid file name", game, NULL);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		exit_with_error("Invalid file extension (expected .cub)", game, NULL);
}

void	check_required_colors(t_game *game)
{
	int	floor_defined;
	int	ceiling_defined;

	floor_defined = (game->map->color_floor[0] != -1
			|| game->map->color_floor[1] != -1
			|| game->map->color_floor[2] != -1);
	ceiling_defined = (game->map->color_ceiling[0] != -1
			|| game->map->color_ceiling[1] != -1
			|| game->map->color_ceiling[2] != -1);
	if (!floor_defined || !ceiling_defined)
		exit_with_error("Missing floor or ceiling color", game, NULL);
}

static int	is_readable(const char *p)
{
	int	fd;

	if (!p)
		return (0);
	fd = open(p, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	validate_config(t_game *game)
{
	if (!game->map)
		return (0);
	if (!is_readable(game->map->texture_north)
		|| !is_readable(game->map->texture_south)
		|| !is_readable(game->map->texture_west)
		|| !is_readable(game->map->texture_east))
		return (0);
	check_required_colors(game);
	return (1);
}
