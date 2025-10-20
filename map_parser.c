/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:11:02 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/10/20 08:54:10 by aarie-c2         ###   ########.fr       */
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

static int	is_valid_rgb(int c)
{
	return(c >= 0 && c <= 255);
}

static int	extract_rgb(char *line, int *rgb)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	split = ft_split(line, ',');
	if (!split || array_len(split) != 3)
		return (0);
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	free_arr(&split);
	if (!is_valid_rgb(r) || !is_valid_rgb(g) || !is_valid_rgb(b))
		return (0);
	rgb[0] = r;
	rgb[1] = g;
	rgb[2] = b;
	return (1);
}

int	parse_rgb(t_map *map, char *line)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (!extract_rgb(line + 2, map->color_floor))
			exit_with_error("Invalid floor RGB format", map, NULL, NULL);
		return (1);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (!extract_rgb(line + 2, map->color_ceiling))
			exit_with_error("Invalid ceiling RGB format", map, NULL, NULL);
		return (1);
	}
	return (0);
}
