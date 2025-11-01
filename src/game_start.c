/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:27:32 by aarie-c2@c1       #+#    #+#             */
/*   Updated: 2025/11/01 12:20:14 by aarie-c2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	mlx_starts(t_game *game)
{
	init_player(game);
	draw_frame(game);
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 6, 1L << 6, mouse_move, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
}

void	start_game(t_map *map, t_game *game)
{
	game_init(game, map);
	game->mlx = mlx_init();
	if (!game->mlx)
		exit_with_error("Failed to init MLX", map, game, NULL);
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, "cub3d_meow");
	if (!game->win)
		exit_with_error("Failed to create window", map, game, NULL);
	load_all_textures(game, map);
	game->img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	if (!game->img)
		exit_with_error("Failed to create image", map, game, NULL);
	game->addr = mlx_get_data_addr(game->img, &game->bpp, \
		&game->line_len, &game->endian);
	if (!game->addr)
		exit_with_error("Failed to get data address", map, game, NULL);
	game->imgt = malloc(sizeof(t_img));
	if (!game->imgt || !minimap_init(game))
		exit_with_error("Failed to init minimap", map, game, NULL);
	mlx_starts(game);
}
