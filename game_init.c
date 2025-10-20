/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:42:20 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/10/20 10:00:13 by aarie-c2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	game_init(t_game *game, t_map *map)
{
	game->mlx = NULL;
	game->win = NULL;
	game->img = NULL;
	game->addr = NULL;
	game->bpp = 0;
	game->line_len = 0;
	game->endian = 0;
	game->map = map;
	game->pos_x = map->player_x + 0.5;
	game->pos_y = map->player_y + 0.5;
	game->dir_x = 0;
	game->dir_y = 0;
	game->plane_x = 0;
	game->plane_y = 0;
}

static int	handle_key(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == 65307)
		close_window(game);
	return (0);
}

static void	set_dir_and_plane(t_game *game, t_vec dir, t_vec plane)
{
	game->dir_x = dir.x;
	game->dir_y = dir.y;
	game->plane_x = plane.x;
	game->plane_y = plane.y;
}

static void	init_player(t_game *game)
{
	game->pos_x = game->map->player_x + 0.5;
	game->pos_y = game->map->player_y + 0.5;

	if (game->map->player_dir == 'N')
		set_dir_and_plane(game, (t_vec){0.0, -1.0}, (t_vec){0.66, 0.0});
	else if (game->map->player_dir == 'S')
		set_dir_and_plane(game, (t_vec){0.0, 1.0}, (t_vec){-0.66, 0.0});
	else if (game->map->player_dir == 'E')
		set_dir_and_plane(game, (t_vec){1.0, 0.0}, (t_vec){0.0, 0.66});
	else if (game->map->player_dir == 'W')
		set_dir_and_plane(game, (t_vec){-1.0, 0.0}, (t_vec){0.0, -0.66});
}

void	start_game(t_map *map)
{
	t_game	game;

	game_init(&game, map);
	game.mlx = mlx_init();
	if (!game.mlx)
		exit_with_error("Failed to init MLX", map, &game, NULL);
	game.win = mlx_new_window(game.mlx, WIN_W, WIN_H, "cub3d_meow");
	if (!game.win)
		exit_with_error("Failed to create window", map, &game, NULL);
	game.img = mlx_new_image(game.mlx, WIN_W, WIN_H);
	if (!game.img)
		exit_with_error("Failed to create image", map, &game, NULL);
	game.addr = mlx_get_data_addr(game.img, &game.bpp, &game.line_len, &game.endian);
	if (!game.addr)
		exit_with_error("Failed to get data address", map, &game, NULL);
	init_player(&game);
	draw_frame(&game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_key_hook(game.win, handle_key, &game);
	mlx_loop(game.mlx);
}
