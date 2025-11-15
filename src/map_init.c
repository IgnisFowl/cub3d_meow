/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aline-arthur <aline-arthur@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 09:41:36 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/11/15 14:11:54 by aline-arthu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_parse_error(int code, t_game *game)
{
	if (code == -1)
		exit_with_error("Invalid floor RGB format", game, NULL);
	else if (code == -2)
		exit_with_error("Invalid ceiling RGB format", game, NULL);
	else if (code == -3)
		exit_with_error("Invalid line", game, NULL);
}

static int	handle_line(char *line, t_game *game, \
	int *map_started, char ***map_lines)
{
	char	*trimmed;
	int		result;

	if (!*map_started)
	{
		trimmed = ft_strtrim(line, " \t\n");
		if (!trimmed || !*trimmed)
		{
			free(trimmed);
			return (0);
		}
		result = process_config_line(trimmed, game);
		if (result == 0)
			result = line_aux(line, map_lines, map_started);
		free(trimmed);
		return (result);
	}
	else
	{
		if (line[0] == '\n')
			return (0);
		add_map_line(map_lines, ft_strdup(line));
	}
	return (0);
}

static int	process_line(char *line, t_game *game, \
    int *map_started, char ***map_lines)
{
	int	error_code;

	if (line_is_blank(line) && *map_started)
	{
		free(line);
		exit_with_error("Empty line inside map", game, NULL);
	}
	error_code = handle_line(line, game, map_started, map_lines);
	free(line);
	if (error_code < 0)
	{
		free_arr(map_lines);
		get_next_line(-1);
		handle_parse_error(error_code, game);
	}
	return (0);
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
		process_line(line, game, &map_started, &map_lines);
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
