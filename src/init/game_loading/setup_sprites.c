/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:44:10 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/21 16:45:57 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	set_positions_of_sprites(t_world *world, t_config *config)
{
	int	i;

	i = 0;
	while (i < world->num_sprites)
	{
		world->sprites[i].pos.x = config->sprites[i].x;
		world->sprites[i].pos.y = config->sprites[i].y;
		i++;
	}
}

/**
 * sets number of sprites
 * and their positions
 * and allocates the sorting arrays
 */
void	setup_sprites(t_data *params, t_config *config)
{
	t_world	*world;

	world = &params->world;
	world->num_sprites = 0;
	world->sprites = malloc(sizeof(*world->sprites));
	world->num_sprites = config->sprite_count;
	world->sprites = malloc(world->num_sprites * sizeof(*world->sprites));
	set_positions_of_sprites(world, config);
	world->sprite_order = malloc(sizeof(*world->sprite_order)
			* world->num_sprites);
	world->sprite_distance = malloc(sizeof(*world->sprite_distance)
			* world->num_sprites);
}
