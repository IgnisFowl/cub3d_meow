/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nade-lim <nade-lim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:10:46 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/11/06 15:46:04 by nade-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_with_error(char *msg, t_map *map, t_game *game, char *str)
{
	if (msg)
		ft_printf("Error\n%s\n", msg); /*alterar*/
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
	t_map	*map;
	t_game	*game;

	if (argc < 2)
	{
		ft_printf("Usage: ./cub3d map.cub\n");
		return (0);
	}
	if (argc == 2)
	{
		map = malloc(sizeof(t_map));
		if (!map)
			return (1);
		map_init(map);
		validate_cub_extension(argv[1], map); /*incluir*/
		start_map(argv[1], map);
		game = malloc(sizeof(t_game));
		if (!game)
			exit_with_error("Failed to alloc game struct", map, NULL, NULL);
		ft_memset(game, 0, sizeof(t_game));
		start_game(map, game);
	}
	ft_printf("nice\n");
	return (0);
}
