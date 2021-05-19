/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:16:54 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 18:17:00 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				key_press(int keycode, t_data *params)
{
	if (is_control_key(keycode))
		params->keystrokes[keycode] = 1;
	return (0);
}
