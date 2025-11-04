/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cats_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aline-arthur <aline-arthur@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:07:06 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/11/04 10:58:33 by aline-arthu      ###   ########.fr       */
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

static void	load_cat_type(t_game *g, int type)
{
	const char	*path;
	int			frame;
	t_texture	*tex;

	frame = 0;
	while (frame < 3)
	{
        path = get_cat_path(type, frame);
        if (!path)
            return ;
        tex = &g->cats.cat_textures[type][frame];
        tex->img = mlx_xpm_file_to_image(g->mlx, (char *)path, 
            &tex->width, &tex->height);
        if (!tex->img)
            return ;
        tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, 
            &tex->line_len, &tex->endian);
        frame++;
	}
}

void	load_cats_textures(t_game *game)
{
	t_texture	*snack;
    int			type;

	type = 0;
	while (type < game->cats.num_cats)
	{
		load_cat_type(game, type);
		type++;
	}
	snack = &game->cats.snack_texture;
	snack->img = mlx_xpm_file_to_image(game->mlx, "textures/churu.xpm", &snack->width, &snack->height);
	snack->addr = mlx_get_data_addr(snack->img, &snack->bpp, &snack->line_len, &snack->endian);
}
