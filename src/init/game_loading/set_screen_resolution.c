/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_screen_resolution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:35:41 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/21 15:54:25 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	set_screen_resolution(t_data *params, t_config *config)
{
	params->resolution.width = config->res.width;
	params->resolution.height = config->res.height;
}
