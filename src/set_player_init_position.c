/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player_init_position.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:41:06 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 22:41:52 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_player_init_position(t_player *player,
		t_pos pos,
		t_dir dir,
		t_plane plane)
{
	player->pos = pos;
	player->dir = dir;
	player->plane = plane;
}
