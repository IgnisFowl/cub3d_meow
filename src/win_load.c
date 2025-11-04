/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aline-arthur <aline-arthur@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:31:26 by aline-arthu       #+#    #+#             */
/*   Updated: 2025/11/04 13:41:43 by aline-arthu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_win_screen(t_game *game)
{
	game->win_screen.img = mlx_xpm_file_to_image(game->mlx,
		"textures/youwin.xpm",
		&game->win_screen.width,
		&game->win_screen.height);
	if (!game->win_screen.img)
		return ;
	game->win_screen.addr = mlx_get_data_addr(game->win_screen.img,
		&game->win_screen.bpp,
		&game->win_screen.line_len,
		&game->win_screen.endian);
}

static void	draw_win_pixel(t_game *game, t_win_draw *draw)
{
	char	*pixel;
	int		color;

	if (draw->tex_x < 0 || draw->tex_x >= draw->tex->width
		|| draw->tex_y < 0 || draw->tex_y >= draw->tex->height)
		return ;
	pixel = draw->tex->addr + (draw->tex_y * draw->tex->line_len
			+ draw->tex_x * (draw->tex->bpp / 8));
	color = *(unsigned int *)pixel;
	if ((color & 0x00FFFFFF) != 0x00000000)
		mlx_pixel_put(game->mlx, game->win, draw->screen_x,
			draw->screen_y, color);
}

static void	draw_win_loop(t_game *game, t_win_draw *draw)
{
	int	x;
	int	y;

	y = 0;
	while (y < draw->tex->height)
	{
		x = 0;
		while (x < draw->tex->width)
		{
			draw->tex_x = x;
			draw->tex_y = y;
			draw->screen_x = (WIN_W - draw->tex->width) / 2 + x;
			draw->screen_y = (WIN_H - draw->tex->height) / 2 + y;
			draw_win_pixel(game, draw);
			x++;
		}
		y++;
	}
}

void	draw_win_screen(t_game *game)
{
	t_win_draw	draw;

	draw.tex = &game->win_screen;
	draw_win_loop(game, &draw);
}
