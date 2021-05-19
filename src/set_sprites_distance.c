/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sprites_distance.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:32:43 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 18:32:51 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * sort sprites from far to close
 */
void			set_sprites_distance(t_world *world, t_player *player)
{
	int	i;

	i = 0;
	while (i < world->num_sprites)
	{
		world->sprite_order[i] = i;
		world->sprite_distance[i] =
			((player->pos.x - world->sprites[i].pos.x) *
					(player->pos.x - world->sprites[i].pos.x) +
				(player->pos.y - world->sprites[i].pos.y) *
					(player->pos.y - world->sprites[i].pos.y));
		i++;
	}
}

