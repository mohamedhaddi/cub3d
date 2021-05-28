/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 17:14:02 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/28 18:32:50 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static void	get_player_pos_map(t_config *config, int i, int j)
{
	char			**map;
	t_player_pos	*player;

	map = config->map;
	player = &config->player;
	player->pos_x = i + .5;
	player->pos_y = j + .5;
	player->dir = map[i][j];
	map[i][j] = '0';
}

int	is_player(t_config *config, int i, int j)
{
	char	**map;

	map = config->map;
	if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
			|| map[i][j] == 'W')
	{
		if (config->g_player_num > 0)
			ft_error(config->map, "Error\nDuplicated player");
		get_player_pos_map(config, i, j);
		config->g_player_num++;
		return (1);
	}
	return (0);
}
