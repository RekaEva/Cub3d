/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:02:58 by lbrianna          #+#    #+#             */
/*   Updated: 2022/10/19 13:30:38 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_game *game, double direction)
{
	double	x;
	double	y;

	x = game->player.x + cos(direction) * STEP;
	y = game->player.y - sin(direction) * STEP;
	if (!ft_strchr("NSWE0", game->map[(int)y][(int)x]))
		return ;
	game->map[(int)game->player.y][(int)game->player.x] = '0';
	game->map[(int)y][(int)x] = game->side;
	game->player.x = x;
	game->player.y = y;
}

int	key_hook(int key, t_game *game)
{
	if (key == ESC)
		do_exit(game);
	else if (key == W)
		move_player(game, game->player_dir);
	else if (key == S)
		move_player(game, game->player_dir - M_PI);
	else if (key == A)
		move_player(game, game->player_dir + M_PI_2);
	else if (key == D)
		move_player(game, game->player_dir - M_PI_2);
	else if (key == LEFT)
		game->player_dir += ROT_STEP * 1;
	else if (key == RIGHT)
		game->player_dir += ROT_STEP * -1;
	return (0);
}
