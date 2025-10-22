/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2@c1r4p1.42sp.org.br <aarie-c2@c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:10:46 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/10/21 21:08:18 by aarie-c2@c1      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_with_error(char *msg, t_map *map, t_game *game, char *str)
{
	if (msg)
		perror(msg);
	if (str)
		free(str);
	if (map)
		free_map(map);
	if (game)
		close_window(game);
	exit(1);
}

int	main(int argc, char **argv)
{
	t_map	map;
	t_game	*game;

	if (argc < 2)
	{
		ft_printf("Usage: ./cub3d map.cub\n");
		return (0);
	}
	if (argc == 2)
	{
		map_init(&map);
		start_map(argv[1], &map);
		game = malloc(sizeof(t_game));
		if (!game)
			exit_with_error("Failed to alloc game struct", &map, NULL, NULL);
		start_game(&map, game);
	}
	ft_printf("nice\n");
	return (0);
}
