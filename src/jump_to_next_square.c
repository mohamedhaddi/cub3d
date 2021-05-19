/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump_to_next_square.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:54:22 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 18:54:34 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * jump to next map square
 */
void			jump_to_next_square(t_ray *ray)
{
	if (ray->side_dist.x < ray->side_dist.y)
		jump_to_next_x_side(ray);
	else
		jump_to_next_y_side(ray);
}
