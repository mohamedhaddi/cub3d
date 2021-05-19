/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_num_of_sprites.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:45:41 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 19:32:25 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_num_of_sprites(t_world *world, t_data *params)
{
	int	x;
	int	y;

	x = 0;
	while (x < params->map_size.width)
	{
		y = 0;
		while (y < params->map_size.height)
		{
			if (world->map[x][y] == 2)
				world->num_sprites += 1;
			y++;
		}
		x++;
	}
}
