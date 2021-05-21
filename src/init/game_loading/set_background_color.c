/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_background_color.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:43:13 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/21 16:29:54 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	set_background_colors(t_world *world, t_config *config)
{
	world->ceiling_color = config->colors.ceiling;
	world->floor_color = config->colors.floor;
}
