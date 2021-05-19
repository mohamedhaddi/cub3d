/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_sprite_height.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:30:31 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 19:32:38 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * calculate height of the sprite on screen
 * using 'transform_y' instead of the real distance prevents fisheye
 */
void	calc_sprite_height(t_sprite *sprite, t_resolution *resolution)
{
	sprite->height = abs((int)(resolution->height / sprite->transform.y));
}
