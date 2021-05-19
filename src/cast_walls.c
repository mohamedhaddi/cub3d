/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:33:24 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 18:34:18 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * SET THE ZBUFFER FOR THE SPRITE CASTING
 */
void			set_zbuffer(int x, t_ray *ray, t_world *world)
{
	world->z_buffer[x] = ray->perp_wall_dist; // perpendicular distance is used
}

/**
 * WALL CASTING LOOP
 */
void			cast_walls(t_resolution *resolution,
				t_player *player,
				t_world *world,
				t_data *params)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < resolution->width)
	{
		calc_ray_params(x, &ray, params, player);
		cast_ray(world, &ray);
		calc_perp_distance(&ray, player);
		calc_line_height(&ray, resolution);
		calc_both_ends_of_vertical_stripe(&ray, resolution);
		calc_wall_x(&ray, player);
		calc_texture_x(&ray);
		set_texture_coordinate_step(&ray);
		set_starting_texture_coordinate(&ray, resolution);
		draw_wall_vertical_stripe(x, &ray, world);
		set_zbuffer(x, &ray, world);
		x++;
	}
}
