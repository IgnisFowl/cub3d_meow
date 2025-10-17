/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:07:16 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/10/17 12:46:57 by aarie-c2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>

# include "libft/include/ft_printf.h"
# include "libft/include/get_next_line.h"
# include "libft/include/libft.h"
# include "minilibx-linux/mlx.h"

typedef struct s_map
{
	char	*texture_north;
	char	*texture_south;
	char	*texture_west;
	char	*texture_east;
	int		color_floor[3];
	int		color_ceiling[3];
	int		width;
	int		height;
	char	**map;
	int		player_x;
	int		player_y;
	char	player_dir;
} t_map;

void    exit_with_error(char *msg, t_map *map, char *str);
void 	map_init(t_map *map);
void	start_map(char *argv);
int 	array_len(char **array);
int		is_map_line(char *line);
void	add_map_line(char ***map_lines, char *line);
int		parse_texture(t_map *map, char *line);
int		parse_rgb(t_map *map, char *line);
void	finalize_map(t_map *map, char **map_lines);

void	free_map(t_map *map);
void	free_arr(char ***arr);

void 	print_map(const t_map *map); //deletar depois

#endif