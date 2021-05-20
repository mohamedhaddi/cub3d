/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:26:27 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 19:49:17 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/**
 * after sorting the sprites, do the projection and draw them
 */
void	draw_sprites(t_world *world,
					t_player *player,
					t_resolution *resolution,
					t_data *params)
{
	t_sprite	sprite;
	int			i;

	i = 0;
	while (i < world->num_sprites)
	{
		make_sprite_pos_relative_to_camera(i, &sprite, world, player);
		transform_sprite_with_inverse_camera_matrix(&sprite,
			resolution,
			player);
		calc_sprite_height(&sprite, resolution);
		calc_start_end_of_stripe(&sprite, resolution);
		calc_sprite_width(&sprite, resolution);
		loop_through_sprite_stripes(&sprite, resolution, world, params);
		i++;
	}
}
