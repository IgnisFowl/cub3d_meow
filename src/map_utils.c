/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nade-lim <nade-lim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:16:19 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/11/06 17:03:19 by nade-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void print_map(const t_map *map)
{
    if (!map || !map->map)
    {
        printf("Map is empty or not initialized.\n");
        return;
    }

    printf("Map dimensions: %d x %d\n", map->width, map->height);
    printf("Map data:\n");

    for (int y = 0; y < map->height; y++)
    {
        printf("[%2d]: ", y);              // print line number padded to 2 digits
        if (map->map[y])
            printf("%.*s\n", map->width, map->map[y]); // print exactly map->width chars
        else
            printf("(null)\n");
    }
	ft_printf("\n ***  MEOWLCOME to our game! ***\n\n");
	ft_printf(" ⋅☆⋅⋆⋅★⋅⋆⋆⋅☆⋅⋆⋅★⋅⋆⋆⋅☆⋅⋆⋅★⋅⋆⋆⋅☆⋅⋆⋅★⋅\n\n");
	ft_printf("Use WASD keys to walk, and use the\n");
	ft_printf("arrow keys or the mouse to turn the\n");
	ft_printf("camera around. Collect snacks, and\n");
	ft_printf("feed the cats by pressing space key.\n\n");
	ft_printf("✦✧✦✧✦✧✦✧     Good luck!    ✦✧✦✧✦✧✦✧\n\n");
	ft_printf(" ⋅☆⋅⋆⋅★⋅⋆⋆⋅☆⋅⋆⋅★⋅⋆⋆⋅☆⋅⋆⋅★⋅⋆⋆⋅☆⋅⋆⋅★⋅\n\n");
}

int	array_len(char **array)
{
	int	count;

	count = 0;
	if (!array)
		return (0);
	while (array[count])
		count++;
	return (count);
}

int	is_map_line(char *line)
{
	int	i;

	if (!line || !*line)
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1'
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W'
			&& line[i] != 'C' && line[i] != 'B'
			&& line[i] != ' ' && line[i] != '\t' 
			&& line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

void	map_init(t_map *map)
{
	map->texture_north = NULL;
	map->texture_south = NULL;
	map->texture_west = NULL;
	map->texture_east = NULL;
	map->color_floor[0] = -1; /* alterar as cores pra -1*/
	map->color_floor[1] = -1;
	map->color_floor[2] = -1;
	map->color_ceiling[0] = -1;
	map->color_ceiling[1] = -1;
	map->color_ceiling[2] = -1; /* alterar as cores pra -1*/
	map->width = 0;
	map->height = 0;
	map->map = NULL;
	map->player_x = -1;
	map->player_y = -1;
	map->player_dir = '\0';
}

void	add_map_line(char ***map_lines, char *line)
{
	int		len;
	char	**new_array;
	int		i;

	i = 0;
	len = array_len(*map_lines);
	new_array = malloc(sizeof(char *) * (len + 2));
	if (!new_array)
		exit_with_error("Mem alloc failed", NULL, NULL, line);
	while (i < len)
	{
		new_array[i] = (*map_lines)[i];
		i++;
	}
	new_array[len] = line;
	new_array[len + 1] = NULL;
	if (*map_lines)
		free(*map_lines);
	*map_lines = new_array;
}

int	is_inside_map(t_map *map, int x, int y)
{
	int	row_len;

	if (y < 0 || y >= map->height)
		return (0);
	row_len = ft_strlen(map->map[y]);
	if (x < 0 || x >= row_len)
		return (0);
	return (1);
}
