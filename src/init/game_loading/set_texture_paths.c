/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture_paths.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:42:20 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/28 16:19:33 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	set_texture_paths(t_world *world, t_config *config)
{
	world->texture_paths.walls_facing_north = config->tex.no;
	world->texture_paths.walls_facing_south = config->tex.so;
	world->texture_paths.walls_facing_east = config->tex.ea;
	world->texture_paths.walls_facing_west = config->tex.we;
}
