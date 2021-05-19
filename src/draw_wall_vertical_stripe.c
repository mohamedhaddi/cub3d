/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_vertical_stripe.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:34:56 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 18:46:59 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * draw a vertical stripe of a wall:
 * - `ray->tex_y = ...` -> Cast the texture coordinate to integer, and mask with
 * (TEX_SIZE - 1) in case of overflow
 * - `if ((color & 0x00FFFFFF) != 0) ...` -> paint pixel if it isn't black,
 * black is the invisible color
 * - y-coordinate is first in buffer because it works per scanline
 */
void			draw_wall_vertical_stripe(int x, t_ray *ray, t_world *world)
{
	int	y;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		ray->tex_y = (int)ray->tex_pos & (TEX_SIZE - 1);
		ray->tex_pos += ray->tex_step;
		int color =
			world->textures[ray->side].addr[TEX_SIZE * ray->tex_y + ray->tex_x];
		if ((color & 0x00FFFFFF) != 0)
			world->buffer[y][x] = color;
		y++;
	}
}
