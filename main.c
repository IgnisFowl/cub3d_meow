/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:10:46 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/10/20 08:52:53 by aarie-c2         ###   ########.fr       */
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

	if (argc < 2)
	{
		ft_printf("Usage: ./cub3d map.cub/n");
		return (0);
	}
	if (argc == 2)
	{
		map_init(&map);
		start_map(argv[1], &map);
		start_game(&map);
	}
	ft_printf("nice\n");
	free_map(&map);
	return (0);
}
