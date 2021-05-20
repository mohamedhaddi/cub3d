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

#include "../../cub3d.h"

/**
 * jump to next map square in y-direction
 */
void	jump_to_next_y_side(t_ray *ray)
{
	ray->side_dist.y += ray->delta_dist.y;
	ray->box.y += ray->step.dir.y;
	if (ray->dir.y > 0)
		ray->side = EA;
	else
		ray->side = WE;
}

/**
 * jump to next map square in x-direction
 */
void	jump_to_next_x_side(t_ray *ray)
{
	ray->side_dist.x += ray->delta_dist.x;
	ray->box.x += ray->step.dir.x;
	if (ray->dir.x > 0)
		ray->side = SO;
	else
		ray->side = NO;
}

/**
 * jump to next map square
 */
void	jump_to_next_square(t_ray *ray)
{
	if (ray->side_dist.x < ray->side_dist.y)
		jump_to_next_x_side(ray);
	else
		jump_to_next_y_side(ray);
}

/**
 * Check if ray has hit a wall
 */
int	is_a_wall_hit(int box)
{
	return (box == 1);
}

/**
 * perform DDA: a loop that increments the ray with 1 square
 * every time until a wall is hit
 */
void	cast_ray(t_world *world, t_ray *ray)
{
	while (is_a_wall_hit(world->map[ray->box.x][ray->box.y]) == 0)
		jump_to_next_square(ray);
}
