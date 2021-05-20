/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture_paths.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:42:20 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/20 19:43:10 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	set_texture_paths(t_world *world)
{
	world->texture_paths.walls_facing_north = "./assets/textures/iron.xpm";
	world->texture_paths.walls_facing_south = "./assets/textures/grass.xpm";
	world->texture_paths.walls_facing_east = "./assets/textures/water.xpm";
	world->texture_paths.walls_facing_west = "./assets/textures/gold.xpm";
	world->texture_paths.sprite = "./assets/textures/sprite.xpm";
}
