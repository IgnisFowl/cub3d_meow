/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 09:41:36 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/11/01 15:55:37 by aarie-c2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	process_config_line(char *trimmed, t_map *map)
{
	if (parse_texture(map, trimmed))
		return (1);
	if (parse_rgb(map, trimmed))
		return (1);
	return (0);
}

static void	line_aux(char *line, char ***map_lines, \
	t_map *map, int *map_started)
{
	if (is_map_line(line))
	{
		*map_started = 1;
		add_map_line(map_lines, ft_strdup(line));
		return ;
	}
	else
		exit_with_error("Invalid line", map, NULL, line);
}

static void	handle_line(char *line, t_map *map, \
	int *map_started, char ***map_lines)
{
	char	*trimmed;

	if (!*map_started)
	{
		trimmed = ft_strtrim(line, " \t\n");
		if (!trimmed || !*trimmed)
		{
			free(trimmed);
			return ;
		}
		if (!process_config_line(trimmed, map))
			line_aux(line, map_lines, map, map_started);
		free(trimmed);
	}
	else
	{
		if (line[0] == '\n')
			return ;
		add_map_line(map_lines, ft_strdup(line));
	}
}

static void	parse_loop(int fd, t_map *map)
{
	char	*line;
	int		map_started;
	char	**map_lines;

	map_started = 0;
	map_lines = NULL;
	line = get_next_line(fd);
	while (line)
	{
		handle_line(line, map, &map_started, &map_lines);
		free(line);
		line = get_next_line(fd);
	}
	finalize_map(map, map_lines);
	free_arr(&map_lines);
}

void	start_map(char *argv, t_map *map)
{
	int		fd;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		exit_with_error("Failed to open map.", map, NULL, NULL);
	else
	{
		parse_loop(fd, map);
		close(fd);
	}
	print_map(map); //for debugging
}
