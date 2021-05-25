/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:44:10 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/25 03:57:39 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	set_positions_of_sprites(t_world *world, t_config *config)
{
	int	i;
	int	j;
	int	c;

	i = 0;
	c = 0;
	while (config->map[i])
	{
		j = 0;
		while (config->map[i][j])
		{
			if (config->map[i][j] == '2')
			{
				world->sprites[c].pos.x = i + 0.5;
				world->sprites[c].pos.y = j + 0.5;
				c++;
			}
			j++;
		}
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
	world->num_sprites = config->sprite_count;
	world->sprites = malloc(world->num_sprites * sizeof(*world->sprites));
	set_positions_of_sprites(world, config);
	world->sprite_order = malloc(sizeof(*world->sprite_order)
			* world->num_sprites);
	world->sprite_distance = malloc(sizeof(*world->sprite_distance)
			* world->num_sprites);
}
