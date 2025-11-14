/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nade-lim <nade-lim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:09:43 by nade-lim          #+#    #+#             */
/*   Updated: 2025/11/14 16:54:46 by nade-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sanitize_map_lines(char **map_lines)
{
	int		i;
	char	*newline;
	char	*carriage;

	if (!map_lines)
		return ;
	i = 0;
	while (map_lines[i])
	{
		newline = ft_strchr(map_lines[i], '\n');
		if (newline)
			*newline = '\0';
		carriage = ft_strchr(map_lines[i], '\r');
		if (carriage)
			*carriage = '\0';
		i++;
	}
}

void	clean_trailing_lines(char **map_lines)
{
	int	i;
	int	last_map_line;

	last_map_line = -1;
	i = 0;
	while (map_lines && map_lines[i])
	{
		if (ft_strchr(map_lines[i], '1') || ft_strchr(map_lines[i], '0')
			|| ft_strchr(map_lines[i], 'N') || ft_strchr(map_lines[i], 'S')
			|| ft_strchr(map_lines[i], 'E') || ft_strchr(map_lines[i], 'W'))
			last_map_line = i;
		i++;
	}
	if (last_map_line >= 0 && map_lines[last_map_line + 1])
	{
		i = last_map_line + 1;
		while (map_lines[i])
		{
			if (!line_is_blank(map_lines[i]))
				exit_with_error("Extra content after map", NULL, NULL, NULL);
			i++;
		}
	}
}

void	check_extra_lines_after_map(char **map_lines, t_map *map)
{
	int	i;
	int	map_has_started;
	int	map_has_ended;

	map_has_started = 0;
	map_has_ended = 0;
	i = 0;
	while (map_lines && map_lines[i])
	{
		if (!map_has_started && ft_strchr(map_lines[i], '1'))
			map_has_started = 1;
		else if (map_has_started && !map_has_ended)
		{
			if (line_is_blank(map_lines[i]))
				map_has_ended = 1;
		}
		else if (map_has_ended)
		{
			if (!line_is_blank(map_lines[i]))
				exit_with_error("Extra content after map", map, NULL, NULL);
		}
		i++;
	}
}

int	line_is_blank(const char *s)
{
	int	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n' && s[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

int	is_only_digits(char *s)
{
	int	i;

	if (!s || !*s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
