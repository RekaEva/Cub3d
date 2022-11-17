/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 12:40:39 by lbrianna          #+#    #+#             */
/*   Updated: 2022/10/19 15:02:15 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_player(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (game->map[++y])
	{
		x = -1;
		while (game->map[y][++x])
		{
			if (ft_strchr("NWES", game->map[y][x]))
			{
				game->player.x = (double)x + 0.5;
				game->player.y = (double)y + 0.5;
				if (game->map[y][x] == 'N')
					game->player_dir = M_PI / 2;
				else if (game->map[y][x] == 'W')
					game->player_dir = M_PI;
				else if (game->map[y][x] == 'S')
					game->player_dir = 3 * (M_PI / 2);
				else if (game->map[y][x] == 'E')
					game->player_dir = 0;
				game->player_start = game->player_dir + FOV / 2;
			}
		}
	}
}

void	bonus_mouse_rotate(t_game *game)
{
	static int		tmp_x;
	int				x;
	int				del_x;
	int				tmp_y;

	mlx_mouse_hide();
	mlx_mouse_get_pos(game->win, &x, &tmp_y);
	del_x = x - tmp_x;
	tmp_x = x;
	if (tmp_x > WIN_WIDTH || tmp_x < 0)
	{
		mlx_mouse_move(game->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
		tmp_x = WIN_WIDTH / 2;
	}
	game->player_dir -= (del_x * (FOV / WIN_WIDTH));
}

int	rendering(t_game *game)
{
	bonus_mouse_rotate(game);
	ft_draw_celling_and_floor(game);
	ray_cast(game);
	draw_mini_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->texture->img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	*data;
	t_game	*game;

	if (argc != 2)
		return_error("Wrong number of arguments\n", 1);
	data = init_data();
	parser(argv, data);
	game = init_game(data);
	set_player(game);
	init_mlx(data, game);
	draw_mini_map(game);
	ray_cast(game);
	mlx_mouse_move(game->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	mlx_hook(game->win, 2, 0, key_hook, game);
	mlx_hook(game->win, 17, 0, do_exit, game);
	mlx_loop_hook(game->mlx, rendering, game);
	mlx_put_image_to_window(game->mlx, game->win, game->texture->img, 0, 0);
	mlx_loop(game->mlx);
	return (0);
}
