/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture_coordinate_step.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:36:35 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 19:31:44 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * set how much to increase the texture coordinate per screen pixel
 */
void	set_texture_coordinate_step(t_ray *ray)
{
	ray->tex_step = 1.0 * TEX_SIZE / ray->line_height;
}
