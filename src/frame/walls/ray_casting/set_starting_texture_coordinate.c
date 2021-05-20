/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_starting_texture_coordinate.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:35:30 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 22:47:41 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

/**
 * set starting texture coordinate
 */
void	set_starting_texture_coordinate(t_ray *ray, t_resolution *resolution)
{
	ray->tex_pos = (ray->draw_start - resolution->height / 2.0
			+ ray->line_height / 2.0) * ray->tex_step;
}
