/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_sprite_pos_relative_to_camera.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:31:54 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 18:31:59 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * translate sprite position to relative to camera
 */
void			make_sprite_pos_relative_to_camera(int sprite_num,
										t_sprite *sprite,
										t_world *world,
										t_player *player)
{
	sprite->pos.x =
		world->sprites[world->sprite_order[sprite_num]].pos.x - player->pos.x;
	sprite->pos.y =
		world->sprites[world->sprite_order[sprite_num]].pos.y - player->pos.y;
}
