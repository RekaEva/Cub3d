/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 12:28:58 by lbrianna          #+#    #+#             */
/*   Updated: 2022/10/18 16:26:58 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_id(char *str, char symb)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != symb)
		++i;
	return (i);
}

char	*get_substr(char *str)
{
	char	*sub;
	int		i;

	i = 0;
	while (*str == SPACE)
		++str;
	if (*str == '\0')
		return_error("Invalid line\n", 8);
	while (str[i] != '\0' && str[i] != '\n')
		++i;
	sub = ft_substr(str, 0, i);
	if (sub == NULL)
		return_error("Memory error\n", 5);
	return (sub);
}

int	get_side(char *str)
{
	if (ft_strncmp(str, "NO ", 3) == 0)
		return (1);
	if (ft_strncmp(str, "SO ", 3) == 0)
		return (2);
	if (ft_strncmp(str, "WE ", 3) == 0)
		return (3);
	if (ft_strncmp(str, "EA ", 3) == 0)
		return (4);
	return_error("Wrong id of the side\n", 9);
	return (0);
}

void	check_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return_error("Could not open file\n", 3);
	if (close(fd) == -1)
		return_error("Could not close file \n", 4);
}

void	define_side_path(t_info *data, char *str)
{
	char	*path;
	int		f;

	(void) data;
	if (find_id(str, NEW_LINE) <= 3)
		return_error("What\n", 55);
	path = get_substr(&str[3]);
	check_path(path);
	f = get_side(str);
	if (f == 1 && data->north == NULL)
		data->north = path;
	else if (f == 2 && data->south == NULL)
		data->south = path;
	else if (f == 3 && data->west == NULL)
		data->west = path;
	else if (f == 4 && data->east == NULL)
		data->east = path;
	else
		return_error("Texture error\n", 10);
}
