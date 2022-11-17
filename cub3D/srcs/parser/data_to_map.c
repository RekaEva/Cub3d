/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_to_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:39:11 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/27 14:48:01 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_height(char *line)
{
	int	i;
	int	num;

	i = -1;
	num = 1;
	while (line[++i])
	{
		if (line[i] == '\n')
			num++;
	}
	return (num);
}

void	func_norme(int j, int w, char *line)
{
	while (j < w)
			line[j++] = SPACE;
	line[j] = '\0';
}

char	**make_map(char *str, int h, int w, int i)
{
	int		j;
	char	*line;
	char	**map;

	map = malloc(sizeof (char *) * (h + 1));
	if (!map)
		return_error("Memory error\n", 5);
	while (*str != '\0')
	{
		line = malloc(sizeof(char) * (w + 1));
		if (!line)
			return_error("Memory error\n", 5);
		j = 0;
		while (*str != '\0' && *str != '\n')
			line[j++] = *(str++);
		func_norme(j, w, line);
		map[i] = line;
		i++;
		if (*str == '\0')
			break ;
		++str;
	}
	map[i] = NULL;
	return (map);
}

void	check_map_2(char **arr, int i, int j)
{
	if (arr[i][j + 1] == SPACE || arr[i][j + 1] == '\0')
		return_error("Map error\n", 13);
	if (j == 0 || arr[i][j - 1] == SPACE)
		return_error("Map error\n", 13);
	if (i == 0 || arr[i - 1][j] == SPACE)
		return_error("Map error\n", 13);
	if (arr[i + 1] == NULL || arr[i + 1][j] == SPACE)
		return_error("Map error\n", 13);
}

void	check_map(t_map *map)
{
	int		i;
	int		j;
	char	**arr;

	arr = map->map;
	i = -1;
	if (map->coord_x == -1)
		return_error("Player error\n", 15);
	while (arr[++i] != NULL)
	{
		j = -1;
		while (arr[i][++j] == SPACE || arr[i][j] == '1'
			|| arr[i][j] == '0' || arr[i][j] == map->side)
		{
			if (arr[i][j] == map->side || arr[i][j] == '0')
				check_map_2(arr, i, j);
		}
		if (arr[i][j] != '\0')
			return_error("Map error\n", 13);
	}
}
