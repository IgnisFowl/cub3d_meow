/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2@c1r4p1.42sp.org.br <aarie-c2@c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:21:37 by aarie-c2@c1       #+#    #+#             */
/*   Updated: 2025/10/21 21:54:41 by aarie-c2@c1      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_texture(t_game *game, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(game->mlx, \
		path, &(texture->width), &(texture->height));
	if (!texture->img)
		return (0);
	texture->addr = mlx_get_data_addr(texture->img, \
		&texture->bpp, &texture->line_len, &texture->endian);
	if (!texture->addr)
		return (0);
	return (1);
}

void	load_all_textures(t_game *game, t_map *map)
{
	if (!load_texture(game, &game->texture_north, map->texture_north))
		exit_with_error("Failed to load north texture", map, game, NULL);
	if (!load_texture(game, &game->texture_south, map->texture_south))
		exit_with_error("Failed to load south texture", map, game, NULL);
	if (!load_texture(game, &game->texture_west, map->texture_west))
		exit_with_error("Failed to load west texture", map, game, NULL);
	if (!load_texture(game, &game->texture_east, map->texture_east))
		exit_with_error("Failed to load east texture", map, game, NULL);
}


void	prepare_texture_params(t_game *game)
{
	t_texture	*texture;

	if (game->raycast.side == 0)
	{
		if (game->raycast.raydirx > 0)
			texture = &game->texture_west;
		else
			texture = &game->texture_east;
	}
	else
	{
		if (game->raycast.raydiry > 0)
			texture = &game->texture_north;
		else
			texture = &game->texture_south;
	}
	game->raycast.tex_x = (int)(game->raycast.wall_x * (double)texture->width);
	if (game->raycast.side == 0 && game->raycast.raydirx > 0)
		game->raycast.tex_x = texture->width - game->raycast.tex_x - 1;
	if (game->raycast.side == 1 && game->raycast.raydiry < 0)
		game->raycast.tex_x = texture->width - game->raycast.tex_x - 1;

	game->raycast.step = 1.0 * texture->height / game->raycast.lineheight;
	game->raycast.tex_pos = (game->raycast.drawstart - \
		WIN_H / 2 + game->raycast.lineheight / 2) * game->raycast.step;
}
