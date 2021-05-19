/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_texture_x.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:37:07 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 18:37:14 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * calculate the x-coordinate on the texture
 * TEX_SIZE is width and height in texels of the textures
 */
void			calc_texture_x(t_ray *ray)
{
	ray->tex_x = (int)(ray->wall_x * (double)TEX_SIZE);
	if (ray->side % 2 == 0 && ray->dir.x > 0)
		ray->tex_x = TEX_SIZE - ray->tex_x - 1;
	if (ray->side % 2 == 1 && ray->dir.y < 0)
		ray->tex_x = TEX_SIZE - ray->tex_x - 1;
}
