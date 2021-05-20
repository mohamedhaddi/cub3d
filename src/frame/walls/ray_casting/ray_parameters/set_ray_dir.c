/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ray_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 19:01:51 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/20 18:20:37 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../cub3d.h"

/** calculate ray position and direction:
 *  - camera_x is x-coordinate in camera space
 */
void	set_ray_dir(int x, t_ray *ray, t_data *params)
{
	t_resolution	*resolution;
	t_player		*player;
	double			camera_x;

	resolution = &params->resolution;
	player = &params->player;
	camera_x = ((2 * x) / (double)resolution->width) - 1;
	ray->dir.x = player->dir.x + player->plane.x * camera_x;
	ray->dir.y = player->dir.y + player->plane.y * camera_x;
}
