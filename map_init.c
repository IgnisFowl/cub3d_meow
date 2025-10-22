/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2@c1r4p1.42sp.org.br <aarie-c2@c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 09:41:36 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/10/21 21:01:45 by aarie-c2@c1      ###   ########.fr       */
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

static void	process_map_line(char *trimmed, \
	t_map *map, int *map_started, char ***map_lines)
{
	if (is_map_line(trimmed))
	{
		if (!*map_started)
			*map_started = 1;
		add_map_line(map_lines, trimmed);
	}
	else
		exit_with_error("Invalid line", map, NULL, trimmed);
}

static void	handle_line(char *line, t_map *map, \
	int *map_started, char ***map_lines)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " \t\n");
	if (!trimmed || !*trimmed)
	{
		free(trimmed);
		return ;
	}
	if (!*map_started)
	{
		if (!process_config_line(trimmed, map))
			process_map_line(trimmed, map, map_started, map_lines);
		else
			free(trimmed);
	}
	else
		process_map_line(trimmed, map, map_started, map_lines);
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
	//print_map(map); //for debugging
}
