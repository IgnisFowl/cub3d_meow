/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_mouse_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nade-lim <nade-lim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 14:43:14 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/11/13 15:30:38 by nade-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	focus_in(t_game *game)
{
	game->mouse_last_x = WIN_W / 2;
	mlx_mouse_move(game->mlx, game->win, WIN_W / 2, WIN_H / 2);
	return (0);
}

int	focus_out(t_game *game)
{
	(void)game;
	return (0);
}
