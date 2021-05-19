/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:44:10 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 22:49:26 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * sets number of sprites
 * and their positions
 * and allocates the sorting arrays
 */
void	setup_sprites(t_data *params)
{
	t_world	*world;

	world = &params->world;
	world->num_sprites = 0;
	world->sprites = malloc(sizeof(*world->sprites));
	calc_num_of_sprites(world, params);
	world->sprites = malloc(world->num_sprites * sizeof(*world->sprites));
	set_positions_of_sprites(world, params);
	world->sprite_order = malloc(sizeof(*world->sprite_order)
			* world->num_sprites);
	world->sprite_distance = malloc(sizeof(*world->sprite_distance)
			* world->num_sprites);
}
