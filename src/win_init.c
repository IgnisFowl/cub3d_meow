/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aline-arthur <aline-arthur@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:16:37 by aline-arthu       #+#    #+#             */
/*   Updated: 2025/11/04 12:05:44 by aline-arthu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_firework_pixel(t_game *game, t_texture *tex, int x, int y, int screen_x, int screen_y)
{
	char	*pixel;
	int	color;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return ;

	pixel = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	color = *(unsigned int *)pixel;

	if (color != -1 && (color & 0x00FFFFFF) != 0)
		mlx_pixel_put(game->mlx, game->win, screen_x, screen_y, color);
}

void	check_win_condition(t_game *game)
{
	int collected;

	collected = get_collected_cats(game);
	if (collected == game->cats.num_cats)
	{
		game->game_won = 1;
	}
}

static void	draw_loop(t_game *game, t_texture *tex, t_firework *fw)
{
	int	x;
	int	y;

	y = 0;
	while (y < tex->height * 4)
	{
		x = 0;
		while (x < tex->width * 4)
		{
			draw_firework_pixel(game, tex, x, y, fw->x + x, fw->y + y);
			x++;
		}
		y++;
	}
}

void    draw_firework(t_game *game, int fw_idx)
{
	t_firework	*fw;
	t_texture	*tex;
	int			frame;

	fw = &game->fireworks[fw_idx];
	frame = fw->current_frame;
	if (frame >= 7)
		return ;
	tex = &fw->textures[frame];
	if (!tex->img)
		return ;
	draw_loop(game, tex, fw);
}

void	render_win_animation(t_game *game)
{
	int	i;

	if (game->win_timer % 4000 == 0)
	{
		i = 0;
		while (i < 3)
		{
			if (game->fireworks[i].current_frame < 7)
				game->fireworks[i].current_frame++;
			i++;
		}
	}
	draw_firework(game, 0);
	draw_firework(game, 1);
	draw_firework(game, 2);

	mlx_string_put(game->mlx, game->win, WIN_W / 2 - 60, 
		WIN_H / 2, 0xFFFFFF, "MEOW, YOU WIN!");
}
