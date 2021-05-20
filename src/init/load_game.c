/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:38:29 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/20 00:24:42 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_game(t_data *params)
{
	t_player	*player;
	t_world		*world;

	player = &params->player;
	world = &params->world;
	spawn_player(params);
	set_player_speed(player);
	set_texture_paths(world);
	set_background_colors(world);
	setup_buffers(params);
	setup_sprites(params);
	load_textures(params);
	initiliaze_keystrokes(&params->keystrokes[0]);
}
