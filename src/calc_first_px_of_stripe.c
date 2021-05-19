/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_first_px_of_stripe.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:50:31 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 19:32:14 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_first_px_of_stripe(t_ray *ray, t_resolution *resolution)
{
	ray->draw_start = -ray->line_height / 2 + resolution->height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
}
