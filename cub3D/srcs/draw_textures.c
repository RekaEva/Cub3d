/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:43:58 by cpollito          #+#    #+#             */
/*   Updated: 2022/10/19 13:59:16 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_the_y(t_game *game, double h, int y, int start)
{
	double	coord;

	coord = round(game->texture->height / h * (y - start));
	if ((int)coord < 0)
		coord = 0;
	else if ((int)coord >= game->texture->height)
		coord = game->texture->height -1;
	return ((int)coord);
}

t_texture	*set_image(t_ray *ray, t_game *game)
{
	if (ray->delta_dist_x - ray->delta_dist_y < 0)
	{
		if (cos(game->player_dir) < 0)
			return (game->texture[2].img);
		return (game->texture[3].img);
	}
	if (sin(game->player_dir) < 0)
		return (game->texture[4].img);
	return (game->texture[1].img);
}

void	choose_image(int *image, t_texture *tex, t_game *game, t_ray *ray)
{
	double	point;
	double	i;

	tex->img = set_image(ray, game);
	tex->mlx = game->mlx;
	tex->addr = mlx_get_data_addr(tex->img, \
		&tex->bpp, &tex->size_line, &tex->endian);
	if (ray->delta_dist_x - ray->delta_dist_y < 0)
		point = game->player.y - ray->delta_dist_x * sin(game->player_dir);
	else
		point = game->player.x + ray->delta_dist_y * cos(game->player_dir);
	i = point - (int)point;
	*image = round(i * game->texture->width);
	if (*image < 0)
		*image = 0;
	else if (*image >= game->texture->width)
		*image = game->texture->width - 1;
}
