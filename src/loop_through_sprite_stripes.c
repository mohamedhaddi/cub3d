/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_through_sprite_stripes.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:27:15 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 22:28:50 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
