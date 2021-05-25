/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 00:34:50 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/25 05:07:14 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * move backwards if no wall behind you
 * - `if (...) ...` -> collision detection: won't move if it is 1 (a wall)
 */
void	move_backward(t_data *params)
{
	t_player	*player;
	t_world		*world;
	double		next_x;
	double		next_y;

	player = &params->player;
	world = &params->world;
	next_x = player->pos.x - player->dir.x * player->speed.move_speed;
	next_y = player->pos.y - player->dir.y * player->speed.move_speed;
	if (world->map[(int)next_x][(int)(player->pos.y)] != '1')
		player->pos.x = next_x;
	if (world->map[(int)(player->pos.x)][(int)next_y] != '1')
		player->pos.y = next_y;
}

/**
 * move forward if no wall in front of you
 * - `if (...) ...` -> collision detection: won't move if it ain't 0 (a wall)
 */
void	move_forward(t_data *params)
{
	t_player	*player;
	t_world		*world;
	double		next_x;
	double		next_y;

	player = &params->player;
	world = &params->world;
	next_x = player->pos.x + player->dir.x * player->speed.move_speed;
	next_y = player->pos.y + player->dir.y * player->speed.move_speed;
	if (world->map[(int)next_x][(int)(player->pos.y)] != '1')
		player->pos.x = next_x;
	if (world->map[(int)(player->pos.x)][(int)next_y] != '1')
		player->pos.y = next_y;
}

/**
 * move to the left if no wall is on the left
 * - `if (...) ...` -> collision detection: won't move if it ain't 0 (a wall)
 */
void	move_left(t_data *params)
{
	t_player	*player;
	t_world		*world;
	double		next_x;
	double		next_y;

	player = &params->player;
	world = &params->world;
	next_x = player->pos.x - player->plane.x * player->speed.move_speed;
	next_y = player->pos.y - player->plane.y * player->speed.move_speed;
	if (world->map[(int)next_x][(int)(player->pos.y)] != '1')
		player->pos.x = next_x;
	if (world->map[(int)(player->pos.x)][(int)next_y] != '1')
		player->pos.y = next_y;
}

/**
 * move to the right if no wall is on the right
 * - `if (...) ...` -> collision detection: won't move if it ain't 0 (a wall)
 */
void	move_right(t_data *params)
{
	t_player	*player;
	t_world		*world;
	double		next_x;
	double		next_y;

	player = &params->player;
	world = &params->world;
	next_x = player->pos.x + player->plane.x * player->speed.move_speed;
	next_y = player->pos.y + player->plane.y * player->speed.move_speed;
	if (world->map[(int)next_x][(int)(player->pos.y)] != '1')
		player->pos.x = next_x;
	if (world->map[(int)(player->pos.x)][(int)next_y] != '1')
		player->pos.y = next_y;
}
