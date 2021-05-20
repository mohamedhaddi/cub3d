/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_ray_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:52:50 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 19:32:36 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	calc_ray_params(int x, t_ray *ray, t_data *params, t_player *player)
{
	set_ray_dir(x, ray, params);
	set_ray_current_box(ray, player);
	set_delta_dist(ray);
	set_step_dir(ray);
	set_side_dist(ray, player);
}
