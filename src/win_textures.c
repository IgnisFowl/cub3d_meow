/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nade-lim <nade-lim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:39:19 by aline-arthu       #+#    #+#             */
/*   Updated: 2025/11/13 15:40:32 by nade-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	build_firework_path(char *path, char *color, int frame)
{
	int		i;
	int		j;
	char	frame_char;

	i = 0;
	j = 0;
	while ("textures/fireworks_"[i])
		path[j++] = "textures/fireworks_"[i++];
	i = 0;
	while (color[i])
		path[j++] = color[i++];
	path[j++] = '_';
	frame_char = '0' + frame + 1;
	path[j++] = frame_char;
	path[j++] = '.';
	path[j++] = 'x';
	path[j++] = 'p';
	path[j++] = 'm';
	path[j] = '\0';
}

static void	load_firework(t_game *game, int fw_idx, char *color)
{
	char	path[50];
	int		frame;

	frame = 0;
	while (frame < 7)
	{
		build_firework_path(path, color, frame);
		game->fireworks[fw_idx].textures[frame].img = \
			mlx_xpm_file_to_image(game->mlx, path,
				&game->fireworks[fw_idx].textures[frame].width,
				&game->fireworks[fw_idx].textures[frame].height);
		game->fireworks[fw_idx].textures[frame].addr = \
			mlx_get_data_addr(game->fireworks[fw_idx].textures[frame].img,
				&game->fireworks[fw_idx].textures[frame].bpp,
				&game->fireworks[fw_idx].textures[frame].line_len,
				&game->fireworks[fw_idx].textures[frame].endian);
		frame++;
	}
}

void	load_fireworks_textures(t_game *game)
{
	load_firework(game, 0, "yellow");
	load_firework(game, 1, "pink");
	load_firework(game, 2, "purple");
	game->fireworks[0].x = WIN_W / 6;
	game->fireworks[0].y = WIN_H / 5;
	game->fireworks[0].current_frame = 0;
	game->fireworks[1].x = WIN_W / 2 - 128;
	game->fireworks[1].y = WIN_H / 6;
	game->fireworks[1].current_frame = 0;
	game->fireworks[2].x = (WIN_W * 5) / 6 - 256;
	game->fireworks[2].y = WIN_H / 5;
	game->fireworks[2].current_frame = 0;
}

static void	draw_firework_pixel(t_game *game, t_firework_draw *draw)
{
	char	*pixel;
	int		color;

	if (draw->tex_x < 0 || draw->tex_x >= draw->tex->width
		|| draw->tex_y < 0 || draw->tex_y >= draw->tex->height)
		return ;
	pixel = draw->tex->addr + (draw->tex_y * draw->tex->line_len
			+ draw->tex_x * (draw->tex->bpp / 8));
	color = *(unsigned int *)pixel;
	if (color != -1 && (color & 0x00FFFFFF) != 0)
		mlx_pixel_put(game->mlx, game->win, draw->screen_x, draw->screen_y,
			color);
}

void	draw_loop(t_game *game, t_firework_draw *draw)
{
	draw->tex_y = 0;
	while (draw->tex_y < draw->tex->height * 4)
	{
		draw->tex_x = 0;
		while (draw->tex_x < draw->tex->width * 4)
		{
			draw->screen_x = draw->fw->x + draw->tex_x;
			draw->screen_y = draw->fw->y + draw->tex_y;
			draw_firework_pixel(game, draw);
			draw->tex_x++;
		}
		draw->tex_y++;
	}
}
