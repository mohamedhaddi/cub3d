/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump_to_next_x_side.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:57:36 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 19:29:19 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
