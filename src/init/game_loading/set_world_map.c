/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_world_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 16:46:45 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/22 17:06:38 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	set_world_map(t_data *params, t_config *config) {
	int i;
	int j;
	char cur;
	t_world *world;

	i = 0;
	world = &params->world;
	world->map = malloc(sizeof(world->map) * config->rows_num);
	while (config->map[i]) {
		world->map[i] = malloc(sizeof(world->map) * ft_strlen(config->map[i]));
		j = 0;
		while(config->map[i][j]) {
			cur = config->map[i][j];
			if (cur == '0')
				world->map[i][j] = 0;
			else if (cur == '1')
				world->map[i][j] = 1;
			else if (cur == '2')
				world->map[i][j] = 2;
			else if (cur == ' ')
				world->map[i][j] = 1;
			j++;
		}
		i++;
	}
}
