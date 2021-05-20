/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ray_current_box.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:58:40 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/20 18:20:24 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../cub3d.h"

/**
 * which box of the map we're in
 */
void	set_ray_current_box(t_ray *ray, t_player *player)
{
	ray->box.x = (int)player->pos.x;
	ray->box.y = (int)player->pos.y;
}
