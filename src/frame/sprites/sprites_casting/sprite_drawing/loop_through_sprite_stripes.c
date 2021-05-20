/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_through_sprite_stripes.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:27:15 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/20 18:11:39 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../cub3d.h"

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

/**
 * loop through every vertical stripe of the sprite on screen
 * the conditions in the if are:
 * 1) it's in front of camera plane so you don't see things behind you
 * 2) it's on the screen (left)
 * 3) it's on the screen (right)
 * 4) z_buffer, with perpendicular distance
 */
void	loop_through_sprite_stripes(t_sprite *sprite,
									t_resolution *resolution,
									t_world *world,
									t_data *params)
{
	int	stripe;
	int	tex_x;

	stripe = sprite->draw_start_x;
	while (stripe < sprite->draw_end_x)
	{
		tex_x = (int)(256
				* (stripe - (-sprite->width / 2 + sprite->screen_x))
				* TEX_SIZE / sprite->width) / 256;
		if (sprite->transform.y > 0
			&& stripe > 0
			&& stripe < resolution->width
			&& sprite->transform.y < world->z_buffer[stripe])
			draw_sprite_vertical_stripe(stripe, tex_x, sprite, params);
		stripe++;
	}
}
