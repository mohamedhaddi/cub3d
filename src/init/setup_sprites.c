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

#include "../cub3d.h"

void	set_positions_of_sprites(t_world *world, t_data *params)
{
	int	x;
	int	i;
	int	y;

	x = 0;
	i = 0;
	while (x < params->map_size.width)
	{
		y = 0;
		while (y < params->map_size.height)
		{
			if (world->map[x][y] == 2)
			{
				world->sprites[i].pos = (t_pos){x + 0.5, y + 0.5};
				i += 1;
			}
			y++;
		}
		x++;
	}
}

void	calc_num_of_sprites(t_world *world, t_data *params)
{
	int	x;
	int	y;

	x = 0;
	while (x < params->map_size.width)
	{
		y = 0;
		while (y < params->map_size.height)
		{
			if (world->map[x][y] == 2)
				world->num_sprites += 1;
			y++;
		}
		x++;
	}
}

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
