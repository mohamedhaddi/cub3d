/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:39:45 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 19:32:04 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * set player's position and spawning orientation in map
 * set the position of each sprite
 */
void	spawn_player(t_data *params)
{
	t_player	*player;
	t_world		*world;
	int			cur_pos;
	int			x;
	int			y;

	player = &params->player;
	world = &params->world;
	x = 0;
	while (x < params->map_size.width)
	{
		y = 0;
		while (y < params->map_size.height)
		{
			cur_pos = world->map[x][y];
			if (cur_pos == 'N' || cur_pos == 'S' || cur_pos == 'E' ||
				cur_pos == 'W')
				world->map[x][y] = 0;
			if (cur_pos == 'N')
				set_player_init_position(player,
											(t_pos){x + 0.5, y + 0.5},
											(t_dir){-1, 0},
											(t_plane){0, 0.66});
			else if (cur_pos == 'S')
				set_player_init_position(player,
											(t_pos){x + 0.5, y + 0.5},
											(t_dir){1, 0},
											(t_plane){0, -0.66});
			else if (cur_pos == 'E')
				set_player_init_position(player,
											(t_pos){x + 0.5, y + 0.5},
											(t_dir){0, 1},
											(t_plane){0.66, 0});
			else if (cur_pos == 'W')
				set_player_init_position(player,
											(t_pos){x + 0.5, y + 0.5},
											(t_dir){0, -1},
											(t_plane){-0.66, 0});
			y++;
		}
		x++;
	}
}
