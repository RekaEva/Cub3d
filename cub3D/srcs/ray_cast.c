/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:12:54 by lbrianna          #+#    #+#             */
/*   Updated: 2022/10/19 13:57:55 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_y(t_game *game, t_ray *ray)
{
	double	del_y;

	if (sin(game->player_dir) > 0)
	{
		game->step_y = -1;
		del_y = (game->player.y) - floor(game->player.y);
	}
	else
	{
		game->step_y = 1;
		del_y = ceil(game->player.y) - game->player.y;
	}
	ray->delta_dist_y = sqrt(del_y * del_y + (del_y / tan(game->player_dir))
			* (del_y / tan(game->player_dir)));
}

void	set_start_rays_and_step(t_game *game, t_ray *ray)
{
	double	del_x;

	if (cos(game->player_dir) < 0)
	{
		game->step_x = -1;
		del_x = (game->player.x) - floor(game->player.x);
	}
	else
	{
		game->step_x = 1;
		del_x = ceil(game->player.x) - game->player.x;
	}
	ray->delta_dist_x = sqrt(del_x * del_x + (tan(game->player_dir) * del_x)
			* (tan(game->player_dir) * del_x));
	set_y(game, ray);
}

void	set_rays(t_game *game, t_ray *ray)
{
	if (ray->delta_dist_x - ray->delta_dist_y < 0)
		ray->delta_dist_x += sqrt(1.0 + (tan(game->player_dir)
					* tan(game->player_dir)));
	else
		ray->delta_dist_y += sqrt(1.0 + 1.0 / tan(game->player_dir) * 1.0
				/ tan(game->player_dir));
	if (ray->delta_dist_x - ray->delta_dist_y < 0)
		game->x_cur += game->step_x;
	else
		game->y_cur += game->step_y;
}

void	find_dist(t_game *game, t_ray *ray, double dir)
{
	set_start_rays_and_step(game, ray);
	game->x_cur = floor(game->player.x);
	game->y_cur = floor(game->player.y);
	if (ray->delta_dist_x - ray->delta_dist_y < 0)
		game->x_cur += game->step_x;
	else
		game->y_cur += game->step_y;
	while (ft_strchr("NWSE0", game->map[game->y_cur][game->x_cur]))
		set_rays(game, ray);
	if (ray->delta_dist_x - ray->delta_dist_y < 0)
		game->dist = ray->delta_dist_x * cos (game->player_dir - dir);
	else
		game->dist = ray->delta_dist_y * cos (game->player_dir - dir);
}

int	ray_cast(t_game *game)
{
	t_ray	*ray;
	double	step;
	double	dir;

	ray = ft_calloc(sizeof(t_ray), 1);
	if (!ray)
		exit(0);
	dir = game->player_dir;
	game->player_start = dir + FOV / 2;
	step = FOV / (WIN_WIDTH - 1);
	while (ray->pix < WIN_WIDTH)
	{
		game->player_dir = game->player_start - ray->pix * step;
		find_dist(game, ray, dir);
		draw_line(game, ray, ray->pix);
		ray->pix++;
	}
	game->player_dir = dir;
	free(ray);
	return (0);
}
