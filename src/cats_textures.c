/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cats_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:07:06 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/11/01 13:20:06 by aarie-c2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_cat_frame(t_sprite *cat)
{
	cat->frame = (cat->frame + 1) % 3;
}

void	update_animations(t_game *game)
{
	int	i;

	game->cats.anim_time += 0.016;
	if (game->cats.anim_time < 0.3)
		return ;
	game->cats.anim_time = 0.0;
	i = 0;
	while (i < game->cats.num_cats)
	{
		if (game->cats.cats[i].active)
			update_cat_frame(&game->cats.cats[i]);
		i++;
	}
}

static const char	*get_cat_path(int type, int frame)
{
	if (type == 0 && frame == 0)
		return ("textures/cata1.xpm");
	if (type == 0 && frame == 1)
		return ("textures/cata2.xpm");
	if (type == 0 && frame == 2)
		return ("textures/cata3.xpm");
	if (type == 1 && frame == 0)
		return ("textures/catb1.xpm");
	if (type == 1 && frame == 1)
		return ("textures/catb2.xpm");
	if (type == 1 && frame == 2)
		return ("textures/catb3.xpm");
	if (type == 2 && frame == 0)
		return ("textures/catc1.xpm");
	if (type == 2 && frame == 1)
		return ("textures/catc2.xpm");
	if (type == 2 && frame == 2)
		return ("textures/catc3.xpm");
	return (NULL);
}

static void	load_cat_type(t_game *g, int type)
{
	const char	*path;
	int			frame;
	t_texture	*tex;

	frame = 0;
	while (frame < 3)
	{
		path = get_cat_path(type, frame);
		tex = &g->cats.cat_textures[type][frame];
		tex->img = mlx_xpm_file_to_image(g->mlx, (char *)path, &tex->width, &tex->height);
		tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len, &tex->endian);
		frame++;
	}
}

void	load_cats_textures(t_game *game)
{
	t_texture	*snack;

	load_cat_type(game, 0);
	load_cat_type(game, 1);
	load_cat_type(game, 2);
	snack = &game->cats.snack_texture;
	snack->img = mlx_xpm_file_to_image(game->mlx, "textures/churu.xpm", &snack->width, &snack->height);
	snack->addr = mlx_get_data_addr(snack->img, &snack->bpp, &snack->line_len, &snack->endian);
}
