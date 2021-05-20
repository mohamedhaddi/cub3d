/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 00:32:29 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/20 01:22:29 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_control_key(int keycode)
{
	return (keycode == LEFT_KEY
		|| keycode == RIGHT_KEY
		|| keycode == W_KEY
		|| keycode == S_KEY
		|| keycode == A_KEY
		|| keycode == D_KEY
		|| keycode == ESC_KEY);
}

int	red_cross_press(t_data *params)
{
	exit_game(params, EXIT_SUCCESS);
	return (0);
}

int	key_release(int keycode, t_data *params)
{
	if (is_control_key(keycode))
		params->keystrokes[keycode] = 0;
	return (0);
}

int	key_press(int keycode, t_data *params)
{
	if (is_control_key(keycode))
		params->keystrokes[keycode] = 1;
	return (0);
}
