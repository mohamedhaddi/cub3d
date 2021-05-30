/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_vertical_stripe.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:34:56 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/30 09:00:52 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

/**
 * draw a vertical stripe of a wall:
 * - `ray->tex_y = ...` -> Cast the texture coordinate to integer, and mask with
 * (TEX_SIZE - 1) in case of overflow
 * - `if ((color & 0x00FFFFFF) != 0) ...` -> paint pixel if it isn't black,
 * black is the invisible color
 * - y-coordinate is first in buffer because it works per scanline
 */
void	draw_wall_vertical_stripe(int x, t_ray *ray, t_world *world)
{
	int	y;
	int	color;
	int	tex_size;

	y = ray->draw_start;
	tex_size = world->textures[ray->side].width;
	while (y < ray->draw_end)
	{
		ray->tex_y = (int)ray->tex_pos & (tex_size - 1);
		ray->tex_pos += ray->tex_step;
		color = world->textures[ray->side]
			.addr[tex_size * ray->tex_y + ray->tex_x];
		if ((color & 0x00FFFFFF) != 0)
			world->buffer[y][x] = color;
		y++;
	}
}
