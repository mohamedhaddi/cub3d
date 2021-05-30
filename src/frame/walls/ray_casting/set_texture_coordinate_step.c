/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture_coordinate_step.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:36:35 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/30 09:01:18 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

/**
 * set how much to increase the texture coordinate per screen pixel
 */
void	set_texture_coordinate_step(t_ray *ray, t_world *world)
{
	int	tex_size;

	tex_size = world->textures[ray->side].width;
	ray->tex_step = 1.0 * tex_size / ray->line_height;
}
