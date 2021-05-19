/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_positions_of_sprites.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:44:44 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 19:31:16 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_positions_of_sprites(t_world *world, t_data *params)
{
	int	x;
	int	i;
	int	y;

	x = 0;
	i = 0;
	while (x < params->map_size.width)
	{
		y = 0;
		while (y < params->map_size.height)
		{
			if (world->map[x][y] == 2)
			{
				world->sprites[i].pos = (t_pos){x + 0.5, y + 0.5};
				i += 1;
			}
			y++;
		}
		x++;
	}
}
