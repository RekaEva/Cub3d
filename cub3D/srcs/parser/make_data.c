/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:34:58 by lbrianna          #+#    #+#             */
/*   Updated: 2022/10/18 16:40:52 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_width(char *line)
{
	int	len;
	int	i;
	int	f;

	i = 0;
	len = 0;
	f = 0;
	if (*line == '\0')
		return_error("MAP ERROR\n", 13);
	while (line[i] != '\0')
	{
		while (line[i] != '\0' && line[i] != '\n')
			i++;
		if (i - f > len)
			len = i - f;
		if (line[i] == '\0')
			break ;
		f = ++i;
	}
	return (len);
}

t_map	*data_to_map(char *str)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (map == NULL)
		return_error("Memory error\n", 5);
	init_map(map);
	map->width = get_width(str);
	map->height = get_height(str);
	if (map->width < 3 || map->height < 3)
		return_error("Map error\n", 13);
	map->map = make_map(str, map->height, map->width, 0);
	init_player(map);
	check_map(map);
	return (map);
}

int	process_texture(char *str, t_info *data)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (str[i] != '\0')
	{
		while (str[i] == NEW_LINE)
			++i;
		if (num == 4)
			return (i);
		define_side_path(data, &str[i]);
		++num;
		i += find_id(&str[i], NEW_LINE);
	}
	if (str[i] == '\0')
		return_error("File error\n", 7);
	return (i);
}

int	process_colors(char *str, t_info *data)
{
	int	i;
	int	color_num;

	i = 0;
	color_num = 0;
	while (str[i] != '\0')
	{
		while (str[i] == NEW_LINE)
			++i;
		if (color_num == 2)
			return (i);
		define_color(&str[i], data);
		++color_num;
		i += find_id(&str[i], NEW_LINE);
	}
	if (str[i] == '\0')
		return_error("File error\n", 7);
	return (i);
}

void	make_data(t_info *data, char *str)
{
	int		i;

	if (str == NULL || str[0] == '\0')
		return_error("File error\n", 7);
	i = process_texture(str, data);
	i += process_colors(&str[i], data);
	data->map = data_to_map(&str[i]);
}
