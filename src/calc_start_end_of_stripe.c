/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_start_end_of_stripe.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:29:30 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 18:29:40 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * calculate lowest and highest pixel to fill in current stripe
 */
void			calc_start_end_of_stripe(t_sprite *sprite, t_resolution *resolution)
{
	sprite->draw_start_y = -sprite->height / 2 + resolution->height / 2;
	if (sprite->draw_start_y < 0)
		sprite->draw_start_y = 0;
	sprite->draw_end_y = sprite->height / 2 + resolution->height / 2;
	if (sprite->draw_end_y >= resolution->height)
		sprite->draw_end_y = resolution->height;
}

