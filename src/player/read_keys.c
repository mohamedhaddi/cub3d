/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:18:54 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 19:30:33 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	read_keys(t_data *params)
{
	if (params->keystrokes[W_KEY])
		move_forward(params);
	if (params->keystrokes[S_KEY])
		move_backward(params);
	if (params->keystrokes[D_KEY])
		move_right(params);
	if (params->keystrokes[A_KEY])
		move_left(params);
	if (params->keystrokes[RIGHT_KEY])
		rotate_right(params);
	if (params->keystrokes[LEFT_KEY])
		rotate_left(params);
	if (params->keystrokes[ESC_KEY])
		exit_game(params, EXIT_SUCCESS);
	draw_frame(params);
	return (0);
}
