/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 17:14:24 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/25 03:46:41 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int	is_sprite(t_config *config, int i, int j)
{
	char	**map;

	map = config->map;
	if (map[i][j] == '2')
	{
		config->sprite_count++;
		return (1);
	}
	return (0);
}
