/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 19:47:19 by cpollito          #+#    #+#             */
/*   Updated: 2022/10/19 14:06:34 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor(t_game *game)
{
	int	x;
	int	y;

	y = WIN_HEIGHT / 2;
	x = 0;
	while (x < WIN_WIDTH)
	{
		y = WIN_HEIGHT / 2;
		while (y < WIN_HEIGHT)
		{
			my_mlx_pixel_put(game->texture, x, y,
				ft_color_define(game->info->floor));
			y++;
		}
		x++;
	}
}

void	ft_draw_celling_and_floor(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEIGHT / 2)
		{
			my_mlx_pixel_put(game->texture, x, y,
				ft_color_define(game->info->ceiling));
			y++;
		}
		x++;
	}
	draw_floor(game);
}

unsigned int	convert_color(t_texture tex, int x, int y)
{
	char	*color;

	color = tex.addr + (y * tex.size_line + x * (tex.bpp / 8));
	return (*(unsigned int *)color);
}

void	set_start_and_y(double h, int *y, int *start)
{
	if (h > WIN_HEIGHT)
	{
		*y = 0;
		*start = (WIN_HEIGHT - h) / 2;
	}
	else
	{
		*y = WIN_HEIGHT / 2 - (int)h / 2;
		*start = *y;
	}
}

void	draw_line(t_game *game, t_ray *ray, int x)
{
	int			y;
	double		h;
	int			start;
	int			image;
	t_texture	tex;

	h = (int)(WIN_HEIGHT / game->dist);
	set_start_and_y(h, &y, &start);
	choose_image(&image, &tex, game, ray);
	while (y < WIN_HEIGHT / 2)
	{
		my_mlx_pixel_put(game->texture, x, y,
			convert_color(tex, image, get_the_y(game, h, y, start)));
		++y;
	}
	while (y < (WIN_HEIGHT / 2 + (int)h / 2) && y < WIN_HEIGHT)
	{
		my_mlx_pixel_put(game->texture, x, y,
			convert_color(tex, image, get_the_y(game, h, y, start)));
		++y;
	}
}
