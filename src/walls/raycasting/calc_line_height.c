/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_line_height.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:51:01 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 19:32:21 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/**
 * Calculate height of line to draw on screen
 */
void	calc_line_height(t_ray *ray, t_resolution *resolution)
{
	ray->line_height = (int)(resolution->height / ray->perp_wall_dist);
}
