/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_all_keystrokes_to_zero.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:47:24 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 17:47:46 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * initiliaze all keystrokes to zero
 */
void			initiliaze_keystrokes(int *keystrokes)
{
	int	i;

	i = 0;
	while (i < 127)
	{
		keystrokes[i] = 0;
		i++;
	}
}
