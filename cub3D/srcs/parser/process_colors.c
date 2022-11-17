/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 12:26:43 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/26 16:14:03 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_color(t_color *color)
{
	if (color->r < 0 || color->r > 255 || color->g < 0
		|| color->g > 255 || color->b < 0 || color->b > 255)
		return_error("Invalid color\n", 11);
}

int	get_floor_ceil(char *str)
{
	if (ft_strncmp(str, "F ", 2) == 0)
		return (3);
	if (ft_strncmp(str, "C ", 2) == 0)
		return (4);
	return_error("Invalid floor/ceiling", 12);
	return (0);
}

int	get_color(char *str)
{
	int	num;

	num = 0;
	while (*str == SPACE)
		++str;
	if (ft_isdigit(*str) == 0)
		return (-1);
	while (ft_isdigit(*str) == 1)
		num = num * 10 + (*(str++) - '0');
	while (*str == SPACE)
		++str;
	if (*str != '\0' && *str != ',' && *str != NEW_LINE)
		return_error("Wrong color id\n", 11);
	return (num);
}

void	define_color(char *str, t_info *data)
{
	int		i;
	t_color	*color;
	char	*sub;

	color = malloc(sizeof(t_color));
	if (color == NULL)
		return_error("Memory allocation error\n", 5);
	sub = get_substr(&str[2]);
	color->r = get_color(sub);
	i = find_id(sub, ',');
	color->g = get_color(&sub[i + 1]);
	i += find_id(&sub[i + 1], ',') + 1;
	color->b = get_color(&sub[i + 1]);
	i += find_id(&sub[i + 1], ',') + 1;
	if (sub[i] != '\0')
		return_error("Wrong color id\n", 11);
	check_color(color);
	i = get_floor_ceil(str);
	if (i == 3 && data->floor == NULL)
		data->floor = color;
	else if (i == 4 && data->ceiling == NULL)
		data->ceiling = color;
	else
		return_error("Color error\n", 11);
	free(sub);
}
