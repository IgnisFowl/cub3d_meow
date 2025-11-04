/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cats_textures_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aline-arthur <aline-arthur@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 10:54:05 by aline-arthu       #+#    #+#             */
/*   Updated: 2025/11/04 11:12:59 by aline-arthu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static const char	*get_cat_path_0_to_2(int type, int frame)
{
	if (type == 0 && frame == 0)
		return ("textures/cat_white_1.xpm");
	if (type == 0 && frame == 1)
		return ("textures/cat_white_2.xpm");
	if (type == 0 && frame == 2)
		return ("textures/cat_white_3.xpm");
	if (type == 1 && frame == 0)
		return ("textures/catb1.xpm");
	if (type == 1 && frame == 1)
		return ("textures/catb2.xpm");
	if (type == 1 && frame == 2)
		return ("textures/catb3.xpm");
	if (type == 2 && frame == 0)
		return ("textures/cat_orange_1.xpm");
	if (type == 2 && frame == 1)
		return ("textures/cat_orange_2.xpm");
	if (type == 2 && frame == 2)
		return ("textures/cat_orange_3.xpm");
	return (NULL);
}

static const char	*get_cat_path_3_to_5(int type, int frame)
{
	if (type == 3 && frame == 0)
		return ("textures/cata1.xpm");
	if (type == 3 && frame == 1)
		return ("textures/cata2.xpm");
	if (type == 3 && frame == 2)
		return ("textures/cata3.xpm");
	if (type == 4 && frame == 0)
		return ("textures/cat_white_a.xpm");
	if (type == 4 && frame == 1)
		return ("textures/cat_white_b.xpm");
	if (type == 4 && frame == 2)
		return ("textures/cat_white_c.xpm");
	if (type == 5 && frame == 0)
		return ("textures/cat_orange_a.xpm");
	if (type == 5 && frame == 1)
		return ("textures/cat_orange_b.xpm");
	if (type == 5 && frame == 2)
		return ("textures/cat_orange_c.xpm");
	return (NULL);
}

static const char	*get_cat_path_6_to_8(int type, int frame)
{
	if (type == 6 && frame == 0)
		return ("textures/catc1.xpm");
	if (type == 6 && frame == 1)
		return ("textures/catc2.xpm");
	if (type == 6 && frame == 2)
		return ("textures/catc3.xpm");
	if (type == 7 && frame == 0)
		return ("textures/cat_orange_i.xpm");
	if (type == 7 && frame == 1)
		return ("textures/cat_orange_ii.xpm");
	if (type == 7 && frame == 2)
		return ("textures/cat_orange_iii.xpm");
	if (type == 8 && frame == 0)
		return ("textures/cat_white_i.xpm");
	if (type == 8 && frame == 1)
		return ("textures/cat_white_ii.xpm");
	if (type == 8 && frame == 2)
		return ("textures/catf_white_iii.xpm");
	return (NULL);
}

const char	*get_cat_path(int type, int frame)
{
	const char	*path;

	if (type < 0 || type >= 9 || frame < 0 || frame >= 3)
		return (NULL);
	path = NULL;
	if (type >= 0 && type <= 2)
		path = get_cat_path_0_to_2(type, frame);
	else if (type >= 3 && type <= 5)
		path = get_cat_path_3_to_5(type, frame);
	else if (type >= 6 && type <= 8)
		path = get_cat_path_6_to_8(type, frame);
	return (path);
}
