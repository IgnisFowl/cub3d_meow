/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:10:46 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/10/17 12:28:26 by aarie-c2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_with_error(char *msg, t_map *map, char *str)
{
	if (msg)
		perror(msg);
	if (str)
		free(str);
	free_map(map);
	exit(1);
}

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		ft_printf("Usage: ./cub3d map.cub/n");
		return (0);
	}
	if (argc == 2)
	{
		start_map(argv[1]);
	}
	ft_printf("nice\n");
	return (0);
}
