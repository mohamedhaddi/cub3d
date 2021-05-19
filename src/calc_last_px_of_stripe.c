/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_last_px_of_stripe.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:49:54 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 19:32:19 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_last_px_of_stripe(t_ray *ray, t_resolution *resolution)
{
	ray->draw_end = ray->line_height / 2 + resolution->height / 2;
	if (ray->draw_end > resolution->height)
		ray->draw_end = resolution->height;
}
