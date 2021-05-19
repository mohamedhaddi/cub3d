/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:46:15 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 22:25:57 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_textures(t_data *params)
{
	t_world	*world;

	world = &params->world;
	world->textures = malloc(sizeof(*world->textures) * TEX_NUM);
	world->textures[NO] = load_image(
			world->texture_paths.walls_facing_south,
			params);
	world->textures[SO] = load_image(
			world->texture_paths.walls_facing_north,
			params);
	world->textures[EA] = load_image(
			world->texture_paths.walls_facing_west,
			params);
	world->textures[WE] = load_image(
			world->texture_paths.walls_facing_east,
			params);
	world->textures[SPRITE_INDEX] = load_image(
			world->texture_paths.sprite,
			params);
}
