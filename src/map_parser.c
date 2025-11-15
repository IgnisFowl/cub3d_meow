/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aline-arthur <aline-arthur@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:11:02 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/11/15 14:08:27 by aline-arthu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	set_texture(char **texture, char *line)
{
	int	prefix_len;

	prefix_len = 3;
	if (*texture)
		free(*texture);
	*texture = ft_strdup(line + prefix_len);
	if (!*texture)
		return (0);
	return (1);
}

int	parse_texture(t_map *map, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (set_texture(&map->texture_north, line));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (set_texture(&map->texture_south, line));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (set_texture(&map->texture_west, line));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (set_texture(&map->texture_east, line));
	return (0);
}

int	process_config_line(char *trimmed, t_game *game)
{
	int	result;

	if (parse_texture(game->map, trimmed))
		return (1);
	result = parse_rgb(game, trimmed);
	if (result < 0)
		return (result);
	if (result > 0)
		return (1);
	return (0);
}

int	line_aux(char *line, char ***map_lines, int *map_started)
{
	if (is_map_line(line))
	{
		*map_started = 1;
		add_map_line(map_lines, ft_strdup(line));
		return (0);
	}
	return (-3);
}
