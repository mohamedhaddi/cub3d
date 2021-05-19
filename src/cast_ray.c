/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:53:20 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 19:39:05 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * perform DDA: a loop that increments the ray with 1 square
 * every time until a wall is hit
 */
void	cast_ray(t_world *world, t_ray *ray)
{
	while (is_a_wall_hit(world->map[ray->box.x][ray->box.y]) == 0)
		jump_to_next_square(ray);
}
