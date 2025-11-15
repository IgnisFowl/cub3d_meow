/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aline-arthur <aline-arthur@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 09:41:36 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/11/15 13:33:18 by aline-arthu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	process_config_line(char *trimmed, t_game *game)
{
	if (parse_texture(game->map, trimmed))
		return (1);
	if (parse_rgb(game, trimmed))
		return (1);
	return (0);
}

static void	line_aux(char *line, char ***map_lines, \
	t_game *game, int *map_started)
{
	if (is_map_line(line))
	{
		*map_started = 1;
		add_map_line(map_lines, ft_strdup(line));
		return ;
	}
	else
		exit_with_error("Invalid line", game, line);
}

static void	handle_line(char *line, t_game *game, \
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
		if (!process_config_line(trimmed, game))
			line_aux(line, map_lines, game, map_started);
		free(trimmed);
	}
	else
	{
		if (line[0] == '\n')
			return ;
		add_map_line(map_lines, ft_strdup(line));
	}
}

static void	parse_loop(int fd, t_game *game)
{
	char	*line;
	int		map_started;
	char	**map_lines;

	map_started = 0;
	map_lines = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (line_is_blank(line) && map_started)
			exit_with_error("Empty line inside map", game, NULL);
		handle_line(line, game, &map_started, &map_lines);
		free(line);
		line = get_next_line(fd);
	}
	if (!validate_config(game))
	{
		free_arr(&map_lines);
		exit_with_error("Missing one or more texture paths", game, NULL);
	}
	sanitize_map_lines(map_lines);
	clean_trailing_lines(game, map_lines);
	finalize_map(game, map_lines);
	free_arr(&map_lines);
}

void	start_map(char *argv, t_game *game)
{
	int		fd;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		exit_with_error("Failed to open map.", game, NULL);
	else
	{
		map_init(game->map);
		validate_cub_extension(argv, game);
		parse_loop(fd, game);
		close(fd);
	}
}
