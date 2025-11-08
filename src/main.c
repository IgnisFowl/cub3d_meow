/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2@c1r4p1.42sp.org.br <aarie-c2@c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:10:46 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/11/07 20:46:45 by aarie-c2@c1      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_with_error(char *msg, t_map *map, t_game *game, char *str)
{
	if (msg)
		ft_printf("Error\n%s\n", msg);
	if (str)
		free(str);
	if (map)
		free_map(map);
	if (game)
		close_window(game);
	exit(1);
}

static void	start(char *map_file)
{
	t_map	*map;
	t_game	*game;

	map = malloc(sizeof(t_map));
	if (!map)
		return ;
	map_init(map);
	validate_cub_extension(map_file, map);
	start_map(map_file, map);
	game = malloc(sizeof(t_game));
	if (!game)
		exit_with_error("Failed to alloc game struct", map, NULL, NULL);
	ft_memset(game, 0, sizeof(t_game));
	game->game_started = 0;
	start_game(map, game);
}

int	main(int argc, char **argv)
{

	if (argc < 2)
	{
		ft_printf("Usage: ./cub3d map.cub\n");
		return (0);
	}
	if (argc == 2)
		start(argv[1]);
	return (0);
}
