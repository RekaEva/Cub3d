/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 13:51:30 by lbrianna          #+#    #+#             */
/*   Updated: 2022/10/19 13:58:56 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	convert_xpm(t_texture *txr, char *path, void *mlx)
{
	txr->img = mlx_xpm_file_to_image(mlx, path, &txr->width, &txr->height);
	if (!txr->img)
		return_error("Texture init error\n", 16);
}

void	get_data_addr(t_texture *txr)
{
	txr->addr = mlx_get_data_addr(txr->img, &txr->bpp,
			&txr->size_line, &txr->endian);
	if (!txr->addr)
		return_error("Texture init error\n", 16);
}

void	make_texture(t_info *data, t_game *game)
{
	t_texture	*texture;

	texture = (t_texture *)malloc(sizeof(t_texture) * 5);
	if (!texture)
		return_error("Memory error\n", 5);
	convert_xpm(&(texture[0]), data->north, game->mlx);
	convert_xpm(&(texture[1]), data->south, game->mlx);
	convert_xpm(&(texture[2]), data->west, game->mlx);
	convert_xpm(&(texture[3]), data->east, game->mlx);
	convert_xpm(&(texture[4]), data->north, game->mlx);
	game->texture = texture;
}

void	init_mlx(t_info *data, t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	make_texture(data, game);
	game->texture->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->texture->addr = mlx_get_data_addr(game->texture->img,
			&game->texture->bpp, &game->texture->size_line,
			&game->texture->endian);
	ft_draw_celling_and_floor(game);
}
