/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:38:29 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/22 16:55:00 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_game(t_data *params, int argc, char **argv)
{
	t_player	*player;
	t_world		*world;
	t_config	config;

	player = &params->player;
	world = &params->world;
	config = parse_file(argc, argv);
	params->is_save = config.is_save;
	// set_map_size(params, &config);
	// generate_world_map(params, &config);
	// world->map = config.map;
	set_screen_resolution(params, &config);
	set_world_map(params, &config);
	load_mlx(params);
	spawn_player(params, &config);
	set_player_speed(player);
	set_texture_paths(world, &config);
	set_background_colors(world, &config);
	setup_buffers(params);
	setup_sprites(params, &config);
	load_textures(params);
	initiliaze_keystrokes(&params->keystrokes[0]);
}
