/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:16:19 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/10/20 08:54:03 by aarie-c2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void print_map(const t_map *map)
{
    printf("Textures:\n");
    printf("  North: %s\n", map->texture_north ? map->texture_north : "NULL");
    printf("  South: %s\n", map->texture_south ? map->texture_south : "NULL");
    printf("  West:  %s\n", map->texture_west  ? map->texture_west  : "NULL");
    printf("  East:  %s\n", map->texture_east  ? map->texture_east  : "NULL");
    
    printf("Colors:\n");
    printf("  Floor: R=%d G=%d B=%d\n",
           map->color_floor[0], map->color_floor[1], map->color_floor[2]);
    printf("  Ceiling: R=%d G=%d B=%d\n",
           map->color_ceiling[0], map->color_ceiling[1], map->color_ceiling[2]);
    
    printf("Map size: %d x %d\n", map->width, map->height);
    
    printf("Player position: (%d, %d) direction: %c\n",
           map->player_x, map->player_y, map->player_dir);
    
    printf("Map data:\n");
    if (map->map)
    {
        for (int y = 0; y < map->height; y++)
            printf("  %s\n", map->map[y]);
    }
    else
    {
        printf("  NULL\n");
    }
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
			&& line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void map_init(t_map *map)
{
	map->texture_north = NULL;
	map->texture_south = NULL;
	map->texture_west = NULL;
	map->texture_east = NULL;
	map->color_floor[0] = 0;
	map->color_floor[1] = 0;
	map->color_floor[2] = 0;
	map->color_ceiling[0] = 0;
	map->color_ceiling[1] = 0;
	map->color_ceiling[2] = 0;
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
