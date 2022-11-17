/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:40:14 by lbrianna          #+#    #+#             */
/*   Updated: 2022/10/19 13:20:34 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_map *map)
{
	int		i;
	int		j;
	int		f;
	char	**arr;

	i = -1;
	arr = map->map;
	f = 1;
	while (arr[++i] != NULL)
	{
		j = -1;
		while (arr[i][++j] != '\0')
		{
			if (arr[i][j] == 'N' || arr[i][j] == 'S'
				|| arr[i][j] == 'W' || arr[i][j] == 'E')
			{
				if (f == -1)
					return_error("More than one player\n", 14);
				f = -1;
				map->coord_x = j;
				map->coord_y = i;
				map->side = arr[i][j];
			}		
		}
	}
}

void	init_map(t_map *map)
{
	map->coord_x = -1;
	map->coord_y = -1;
	map->height = -1;
	map->width = -1;
	map->map = NULL;
	map->side = '\0';
}

t_info	*init_data(void)
{
	t_info	*data;

	data = (t_info *)malloc(sizeof(t_info));
	if (!data)
		return_error("Memory error\n", 5);
	data->north = NULL;
	data->south = NULL;
	data->west = NULL;
	data->east = NULL;
	data->ceiling = NULL;
	data->floor = NULL;
	return (data);
}

t_game	*init_game(t_info *data)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->info = data;
	game->side = data->map->side;
	game->map = data->map->map;
	return (game);
}
