/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 19:00:59 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 19:00:59 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * clear buffer (by setting floor and ceiling colors)
 */
void			draw_background(t_data *params)
{
	t_world			*world;
	t_resolution	*resolution;
	int				x;
	int				y;

	world = &params->world;
	resolution = &params->resolution;
	x = 0;
	while (x < resolution->width)
	{
		y = 0;
		while (y < resolution->height)
		{
			if (y < resolution->height / 2)
				world->buffer[y][x] = world->ceiling_color;
			else
				world->buffer[y][x] = world->floor_color;
			y++;
		}
		x++;
	}
}
