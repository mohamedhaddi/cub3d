/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_both_ends_of_vertical_stripe.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:48:48 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 19:32:10 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * calculate lowest and highest pixel to fill in current stripe
 */
void	calc_both_ends_of_vertical_stripe(t_ray *ray, t_resolution *resolution)
{
	calc_first_px_of_stripe(ray, resolution);
	calc_last_px_of_stripe(ray, resolution);
}
