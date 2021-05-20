/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_perp_distance.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:51:58 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 19:36:10 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/**
 * Calculate perpendicular distance projected on camera direction (Euclidean
 * distance will give fisheye effect!)
 */
void	calc_perp_distance(t_ray *ray, t_player *player)
{
	if (ray->side % 2 == 0)
		ray->perp_wall_dist = (ray->box.x - player->pos.x
				+ (1.0 - ray->step.dir.x) / 2) / ray->dir.x;
	else
		ray->perp_wall_dist = (ray->box.y - player->pos.y
				+ (1.0 - ray->step.dir.y) / 2) / ray->dir.y;
}
