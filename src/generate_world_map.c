/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_world_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:31:58 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 17:32:27 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * temporary function before parsing the map
 */
void			generate_world_map(t_data *params)
{
	t_world	*world;
	int		i;
	int		j;
	int		new_dir;
	int		new_x_pos;
	int		new_y_pos;
	int		new_pos;

	world = &params->world;
	world->map = malloc(sizeof(world->map) * params->map_size.width);
	i = 0;
	while (i < params->map_size.width)
	{
		world->map[i] = malloc(sizeof(*world->map) * params->map_size.height);
		j = 0;
		while (j < params->map_size.height)
		{
			if ((i == 0) || (j == 0) || (i == params->map_size.width - 1) ||
				(j == params->map_size.height - 1))
			{
				world->map[i][j] = 1;
			}
			else
			{
				world->map[i][j] = rand() % 6;
				if (world->map[i][j] == 4 || world->map[i][j] == 5)
					world->map[i][j] = 0;
				if (world->map[i][j] == 3)
					world->map[i][j] = 1;
			}
			j++;
		}
		i++;
	}
	
	char dirs[4] = {'N', 'S', 'E', 'W'};
	new_dir = rand() % 4;
	new_x_pos = rand() % (params->map_size.width - 1) + 1;
	new_y_pos = rand() % (params->map_size.height - 1) + 1;
	new_pos = world->map[new_x_pos][new_y_pos];
	while (new_pos > 0)
	{
		new_x_pos = rand() % (params->map_size.width - 1) + 1;
		new_y_pos = rand() % (params->map_size.height - 1) + 1;
		new_pos = world->map[new_x_pos][new_y_pos];
	}
	world->map[new_x_pos][new_y_pos] = dirs[new_dir];
	i = 0;
	while (i < params->map_size.width)
	{
		printf("\x1B[37m\"");
		j = 0;
		while (j < params->map_size.height)
		{
			if (world->map[i][j] > 2)
				printf("\x1B[31m%c, ", world->map[i][j]);
			else
				printf("\x1B[37m%d, ", world->map[i][j]);
			j++;
		}
		printf("\b\b\"\n");
		i++;
	}
}

/**
 * void			generate_world_map(t_data *params) {
 * 	t_world *world;
 * 
 * 	world = &params->world;
 * 	world->map = malloc(sizeof(world->map) * params->map_size.width);
 * 
 * 	int map_buffer[24][24] = {
 * 		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
 * 1}, {1, 0, 0, 0, 0, 2, 2, 1, 0, 0, 0, 0, 2, 2, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1}, {1,
 * 0, 1, 2, 2, 0, 2, 2, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 2, 0, 0, 1}, {1, 0, 0,
 * 2, 2, 2, 2, 0, 0, 2, 2, 0, 2, 0, 1, 0, 0, 0, 1, 0, 0, 2, 0, 1}, {1, 0, 0, 2, 0,
 * 0, 2, 0, 1, 0, 0, 2, 0, 0, 2, 2, 1, 0, 0, 'S', 0, 1, 0, 1}, {1, 0, 1, 2, 1, 0,
 * 2, 0, 1, 0, 0, 0, 0, 2, 2, 0, 2, 0, 0, 0, 2, 0, 2, 1}, {1, 2, 2, 0, 0, 1, 0, 2,
 * 0, 1, 0, 2, 2, 2, 2, 0, 1, 2, 0, 0, 2, 0, 0, 1}, {1, 0, 2, 0, 2, 0, 0, 0, 0, 0,
 * 0, 0, 1, 2, 1, 1, 2, 2, 0, 1, 1, 0, 0, 1}, {1, 1, 1, 0, 1, 0, 0, 0, 0, 2, 0, 0,
 * 0, 0, 0, 0, 2, 1, 1, 0, 0, 0, 0, 1}, {1, 2, 2, 0, 2, 0, 2, 1, 1, 2, 0, 0, 0, 1,
 * 0, 1, 0, 0, 0, 0, 0, 1, 0, 1}, {1, 0, 0, 2, 0, 0, 2, 2, 0, 2, 0, 1, 0, 0, 0, 2,
 * 0, 1, 0, 2, 2, 0, 1, 1}, {1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
 * 0, 0, 0, 1, 0, 1}, {1, 0, 1, 2, 0, 0, 2, 2, 0, 2, 0, 2, 1, 0, 0, 1, 0, 2, 0, 0,
 * 2, 1, 0, 1}, {1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 1, 2, 2, 0, 0, 1, 0, 1, 0, 0,
 * 0, 1}, {1, 1, 0, 2, 2, 1, 2, 0, 2, 0, 0, 0, 2, 2, 0, 0, 2, 0, 0, 0, 0, 0, 1, 1},
 * 		{1, 2, 0, 0, 2, 0, 0, 1, 1, 0, 2, 1, 0, 0, 0, 0, 1, 0, 1, 0, 2, 0, 0,
 * 1}, {1, 0, 0, 2, 0, 0, 0, 2, 0, 0, 1, 2, 2, 2, 2, 0, 0, 1, 0, 0, 0, 0, 2, 1}, {1,
 * 0, 0, 2, 0, 0, 0, 0, 2, 0, 1, 0, 0, 1, 0, 0, 2, 2, 2, 0, 1, 0, 2, 1}, {1, 1, 0,
 * 1, 0, 0, 1, 0, 2, 0, 0, 0, 0, 1, 0, 0, 2, 2, 0, 1, 1, 0, 1, 1}, {1, 0, 0, 2, 1,
 * 0, 1, 2, 0, 0, 2, 1, 0, 2, 0, 0, 2, 0, 0, 1, 2, 2, 0, 1}, {1, 2, 0, 0, 2, 0, 0,
 * 0, 0, 0, 1, 0, 0, 0, 2, 0, 2, 2, 0, 0, 0, 0, 1, 1}, {1, 0, 0, 2, 1, 0, 2, 0, 1,
 * 0, 0, 2, 2, 0, 0, 0, 1, 0, 1, 0, 0, 2, 0, 1}, {1, 0, 0, 2, 0, 2, 0, 2, 1, 2, 0,
 * 1, 0, 0, 0, 0, 1, 0, 1, 2, 0, 1, 0, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
 * 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
 * 	};
 * 
 * 	for (int i = 0; i < params->map_size.width; i++)
 * 	{
 * 		world->map[i] = malloc(sizeof(*world->map) * params->map_size.height);
 * 		for (int j = 0; j < params->map_size.height; j++)
 * 			world->map[i][j] = map_buffer[i][j];
 * 	}
 * 
 * 	// print map in stdout
 * 	for (int i = 0; i < params->map_size.width; i++)
 * 	{
 * 		printf("\x1B[37m\"");
 * 		for (int j = 0; j < params->map_size.height; j++)
 * 		{
 * 			if (world->map[i][j] > 2)
 * 				printf("\x1B[31m%c, ", world->map[i][j]);
 * 			else
 * 				printf("\x1B[37m%d, ", world->map[i][j]);
 * 		}
 * 		printf("\b\b\"\n");
 * 	}
 * }
 */
