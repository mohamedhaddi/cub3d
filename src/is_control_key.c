/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_control_key.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:18:08 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 19:29:12 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_control_key(int keycode)
{
	return (keycode == LEFT_KEY || keycode == RIGHT_KEY || keycode == W_KEY ||
			keycode == S_KEY || keycode == A_KEY || keycode == D_KEY ||
			keycode == ESC_KEY);
}
