/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:24:19 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/24 22:46:21 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * this is the function that draws a whole frame
 * every time a control key is pressed
 */
int	draw_frame(t_data *params)
{
	t_mlx			*mlx;
	t_img_data		*img;
	t_player		*player;
	t_world			*world;
	t_resolution	*resolution;

	mlx = &params->mlx;
	img = &params->img;
	player = &params->player;
	world = &params->world;
	resolution = &params->resolution;
	draw_background(params);
	cast_walls(resolution, player, world, params);
	draw_buffer(resolution, world, img, mlx);
	return (0);
}
