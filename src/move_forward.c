/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_forward.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:23:37 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 22:34:36 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * move forward if no wall in front of you
 * - `if (...) ...` -> collision detection: won't move if it ain't 0 (a wall)
 */
void	move_forward(t_data *params)
{
	t_player	*player;
	t_world		*world;

	player = &params->player;
	world = &params->world;
	if (world->map[(int)(player->pos.x
			+ player->dir.x
			* player->speed.move_speed)]
			[(int)(player->pos.y)]
			% 2 == 0)
		player->pos.x += player->dir.x * player->speed.move_speed;
	if (world->map[(int)(player->pos.x)][(int)(player->pos.y
			+ player->dir.y
			* player->speed.move_speed)]
			% 2 == 0)
		player->pos.y += player->dir.y * player->speed.move_speed;
}
