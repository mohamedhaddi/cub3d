/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:24:47 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 19:42:48 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_sprites(t_world *world,
					t_player *player,
					t_resolution *resolution,
					t_data *params)
{
	set_sprites_distance(world, player);
	sort_sprites(world->sprite_order,
		world->sprite_distance,
		world->num_sprites);
	draw_sprites(world, player, resolution, params);
}
