/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_define.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 14:06:34 by cpollito          #+#    #+#             */
/*   Updated: 2022/10/06 16:23:13 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	ft_hex_for_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

unsigned int	ft_color_define(t_color *color)
{
	unsigned int	hex_color;

	hex_color = ft_hex_for_color(color->r, color->g, color->b);
	return (hex_color);
}
