/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:39:45 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/21 16:26:49 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	set_player_init_position(t_player *player,
		t_pos pos,
		t_dir dir,
		t_plane plane)
{
	player->pos = pos;
	player->dir = dir;
	player->plane = plane;
}

/**
 * set player's position and spawning orientation in map
 * set the position of each sprite
 */
void	spawn_player(t_data *params, t_config *config)
{
	t_player	*player;
	t_world		*world;
	char		cur_pos;
	int			x;
	int			y;

	player = &params->player;
	world = &params->world;
	cur_pos = config->player.dir;
	x = config->player.pos_x;
	y = config->player.pos_y;
	if (cur_pos == 'N')
		set_player_init_position(
			player, (t_pos){x + 0.5, y + 0.5},
			(t_dir){-1, 0}, (t_plane){0, 0.66});
	else if (cur_pos == 'S')
		set_player_init_position(
			player, (t_pos){x + 0.5, y + 0.5},
			(t_dir){1, 0}, (t_plane){0, -0.66});
	else if (cur_pos == 'E')
		set_player_init_position(
			player, (t_pos){x + 0.5, y + 0.5},
			(t_dir){0, 1}, (t_plane){0.66, 0});
	else if (cur_pos == 'W')
		set_player_init_position(player, (t_pos){x + 0.5, y + 0.5},
			(t_dir){0, -1}, (t_plane){-0.66, 0});
}
