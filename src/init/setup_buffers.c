/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_buffers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:43:40 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 22:48:41 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	setup_buffers(t_data *params)
{
	t_world	*world;
	int		i;

	world = &params->world;
	world->buffer = malloc(sizeof(*world->buffer)
			* params->resolution.height);
	i = 0;
	while (i < params->resolution.height)
	{
		world->buffer[i] = malloc(sizeof(*world->buffer[i])
				* params->resolution.width);
		i++;
	}
	world->z_buffer = malloc(sizeof(*world->z_buffer)
			* params->resolution.width);
}
