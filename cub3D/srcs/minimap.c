/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:31:50 by cpollito          #+#    #+#             */
/*   Updated: 2022/10/19 15:24:40 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	scale(t_game *game, int x, int y, int scale)
{
	int	pix_x;
	int	pix_y;

	pix_x = (x + 1) * scale;
	pix_y = (y + 1) * scale;
	x = x * scale;
	y = y * scale;
	while (y < pix_y)
	{
		while (x < pix_x)
		{
			my_mlx_pixel_put(game->texture, x, y, 0x505050);
			x++;
		}
		x = x - scale;
		y++;
	}
}

void	player(t_game *game, int x, int y, int scale)
{
	int	pix_x;
	int	pix_y;

	pix_x = (x + 1) * scale;
	pix_y = (y + 1) * scale;
	x = x * scale;
	y = y * scale;
	while (y < pix_y)
	{
		while (x < pix_x)
		{
			my_mlx_pixel_put(game->texture, x, y, 0x7b1800);
			x++;
		}
		x = x - scale;
		y++;
	}
}

void	draw_mini_map(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1')
				scale(game, x, y, SCALE_FOR_MP);
			if (game->map[y][x] == 'N' || game->map[y][x] == 'W'
					|| game->map[y][x] == 'E' || game->map[y][x] == 'S')
				player(game, x, y, SCALE_FOR_MP);
			x++;
		}
		y++;
	}
}
