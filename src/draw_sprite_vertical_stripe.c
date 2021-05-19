/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_vertical_stripe.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:28:03 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 19:48:06 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * - 256 and 128 factors to avoid floats
 * - `color` -> gets current color from the sprite texture
 * - `if ((color & 0x00FFFFFF) != 0) ...` -> paint pixel if it isn't black,
 * black is the invisible color
 */
void	draw_sprite_vertical_stripe(int stripe,
									int tex_x,
									t_sprite *sprite,
									t_data *params)
{
	t_world			*world;
	int				y;
	int				d;
	int				tex_y;
	int				color;

	world = &params->world;
	y = sprite->draw_start_y;
	while (y < sprite->draw_end_y)
	{
		d = (y) * 256 - params->resolution.height * 128 + sprite->height * 128;
		tex_y = ((d * TEX_SIZE) / sprite->height) / 256;
		color = world->textures[SPRITE_INDEX].addr[TEX_SIZE * tex_y + tex_x];
		if ((color & 0x00FFFFFF) != 0)
			world->buffer[y][stripe] = color;
		y++;
	}
}
