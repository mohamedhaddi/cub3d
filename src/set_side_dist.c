/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_side_dist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:59:43 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 19:31:29 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * calculate initial side_dist
 */
void	set_side_dist(t_ray *ray, t_player *player)
{
	if (ray->dir.x < 0)
		ray->side_dist.x = (player->pos.x - ray->box.x) * ray->delta_dist.x;
	else
		ray->side_dist.x = (ray->box.x + 1.0 - player->pos.x) * ray->delta_dist.x;
	if (ray->dir.y < 0)
		ray->side_dist.y = (player->pos.y - ray->box.y) * ray->delta_dist.y;
	else
		ray->side_dist.y = (ray->box.y + 1.0 - player->pos.y) * ray->delta_dist.y;
}
