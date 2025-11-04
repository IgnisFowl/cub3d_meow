/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aline-arthur <aline-arthur@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:16:37 by aline-arthu       #+#    #+#             */
/*   Updated: 2025/11/04 13:36:02 by aline-arthu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_win_condition(t_game *game)
{
	int collected;

	collected = get_collected_cats(game);
	if (collected == game->cats.num_cats)
		game->game_won = 1;
}

void	draw_firework(t_game *game, int fw_idx)
{
	t_firework_draw	draw;

	draw.fw = &game->fireworks[fw_idx];
	if (draw.fw->current_frame >= 7)
		return ;
	draw.tex = &draw.fw->textures[draw.fw->current_frame];
	if (!draw.tex->img)
		return ;
	draw_loop(game, &draw);
}

void	render_win_animation(t_game *game)
{
	int	i;

	if (game->win_timer % 10000 == 0)
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
	draw_win_screen(game);
}
