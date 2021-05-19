/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump_to_next_y_side.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:56:35 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 18:56:43 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * jump to next map square in y-direction
 */
void			jump_to_next_y_side(t_ray *ray)
{
	ray->side_dist.y += ray->delta_dist.y;
	ray->box.y += ray->step.dir.y;
	if (ray->dir.y > 0)
		ray->side = EA;
	else
		ray->side = WE;
}
