/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rgb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aline-arthur <aline-arthur@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 14:02:03 by aline-arthu       #+#    #+#             */
/*   Updated: 2025/11/15 14:02:33 by aline-arthu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_rgb(int c)
{
	return (c >= 0 && c <= 255);
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
	if (!is_only_digits(split[0])
		|| !is_only_digits(split[1])
		|| !is_only_digits(split[2]))
	{
		free_arr(&split);
		return (0);
	}
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

int	parse_rgb(t_game *game, char *line)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (!extract_rgb(line + 2, game->map->color_floor))
			return (-1);
		return (1);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (!extract_rgb(line + 2, game->map->color_ceiling))
			return (-2);
		return (1);
	}
	return (0);
}
