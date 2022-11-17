/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:20:35 by cpollito          #+#    #+#             */
/*   Updated: 2022/10/19 14:06:43 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_texture *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->size_line
			+ x * (data->bpp / 8));
	*(unsigned int *) dst = color;
}

int	return_error(char *str, int code)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	exit(code);
}

int	do_exit(t_game *game)
{
	(void)game;
	exit(0);
	return (0);
}
