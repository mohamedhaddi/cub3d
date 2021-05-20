/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_wall_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:37:46 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 19:38:17 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

/**
 * calculate value of wall_x (where exactly the wall was hit):
 * The value wallX represents the exact value where the wall
 * was hit, not just the integer coordinates of the wall.
 * This is required to know which x-coordinate of the texture
 * we have to use. This is calculated by first calculating
 * the exact x or y coordinate in the world, and then substracting
 * the integer value of the wall off it.
 * Note that even if it's called wallX, it's actually an y-coordinate
 * of the wall if side==1, but it's always the x-coordinate of the texture.
 */
void	calc_wall_x(t_ray *ray, t_player *player)
{
	if (ray->side % 2 == 0)
		ray->wall_x = player->pos.y + ray->perp_wall_dist * ray->dir.y;
	else
		ray->wall_x = player->pos.x + ray->perp_wall_dist * ray->dir.x;
	ray->wall_x -= floor(ray->wall_x);
}
