/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_left.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:21:25 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 22:36:01 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * move to the left if no wall is on the left
 * - `if (...) ...` -> collision detection: won't move if it ain't 0 (a wall)
 */
void	move_left(t_data *params)
{
	t_player	*player;
	t_world		*world;

	player = &params->player;
	world = &params->world;
	if (world->map[(int)(player->pos.x
			- player->plane.x
			* player->speed.move_speed)]
			[(int)(player->pos.y)]
			% 2 == 0)
		player->pos.x -= player->plane.x * player->speed.move_speed;
	if (world->map[(int)(player->pos.x)][(int)(player->pos.y
			- player->plane.y
			* player->speed.move_speed)]
			% 2 == 0)
		player->pos.y -= player->plane.y * player->speed.move_speed;
}
