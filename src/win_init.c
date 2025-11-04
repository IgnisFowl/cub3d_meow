/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aline-arthur <aline-arthur@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:16:37 by aline-arthu       #+#    #+#             */
/*   Updated: 2025/11/04 11:33:33 by aline-arthu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_win_condition(t_game *game)
{
	int collected;

	collected = get_collected_cats(game);
	if (collected == game->cats.num_cats)
	{
		game->game_won = 1;
	}
}

void	render_win_animation(t_game *game)
{
	
}