/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_step_dir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 19:00:26 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 19:31:40 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * what direction to step in x or y-direction (either +1 or -1)
 */
void	set_step_dir(t_ray *ray)
{
	if (ray->dir.x < 0)
		ray->step.dir.x = -1;
	else
		ray->step.dir.x = 1;
	if (ray->dir.y < 0)
		ray->step.dir.y = -1;
	else
		ray->step.dir.y = 1;
}
