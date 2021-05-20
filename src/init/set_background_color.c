/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_background_color.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:43:13 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 19:30:50 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_background_colors(t_world *world)
{
	world->ceiling_color = 0xD1F1F2;
	world->floor_color = 0xF7EDD9;
}
