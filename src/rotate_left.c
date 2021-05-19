/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_left.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:19:40 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 19:30:43 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * rotate to the left:
 * - both camera direction and camera plane must be rotated
 */
void	rotate_left(t_data *params)
{
	double		old_dir_x;
	double		old_plane_x;
	t_player	*player;
	t_world		*world;

	player = &params->player;
	world = &params->world;
	old_dir_x = player->dir.x;
	player->dir.x = player->dir.x * cos(player->speed.rot_speed) -
		player->dir.y * sin(player->speed.rot_speed);
	player->dir.y = old_dir_x * sin(player->speed.rot_speed) +
		player->dir.y * cos(player->speed.rot_speed);
	old_plane_x = player->plane.x;
	player->plane.x = player->plane.x * cos(player->speed.rot_speed) -
		player->plane.y * sin(player->speed.rot_speed);
	player->plane.y = old_plane_x * sin(player->speed.rot_speed) +
		player->plane.y * cos(player->speed.rot_speed);
}
