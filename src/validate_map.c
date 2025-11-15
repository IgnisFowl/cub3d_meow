/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aline-arthur <aline-arthur@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:09:44 by nade-lim          #+#    #+#             */
/*   Updated: 2025/11/15 12:42:52 by aline-arthu      ###   ########.fr       */
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

static int	check_invalid_chars(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map->height)
	{
		clean_line(game->map->map[y]);
		x = 0;
		while (game->map->map[y][x])
		{
			if (!is_valid_tile(game->map->map[y][x]))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

static int	check_single_player(t_game *game)
{
	int	count;
	int	y;
	int	x;

	count = 0;
	y = -1;
	while (++y < game->map->height)
	{
		x = -1;
		while (++x < (int)ft_strlen(game->map->map[y]))
			if (ft_strchr("NSEW", game->map->map[y][x]))
				count++;
	}
	if (count == 0)
		return (0);
	if (count > 1)
		return (0);
	return (1);
}

void	validate_map(t_game *game, char **map_lines)
{
	if (!check_invalid_chars(game) || !check_single_player(game) \
	|| !check_walls_closed(game))
	{
		free_arr(&map_lines);
		exit_with_error("Invalid map!", game, NULL);
	}
}
