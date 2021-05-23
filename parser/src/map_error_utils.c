/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 17:13:25 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/23 19:06:05 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	check_if_valid(t_config *config, int i, int j)
{
	char	**map;

	map = config->map;
	if (!is_player(config, i, j)
		&& !is_sprite(config, i, j)
		&& map[i][j] != '1' && map[i][j] != '0'
		&& map[i][j] != ' ')
		raise_map_error(config->map, i, j);
}

void	check_next_row(char **map, t_point point, char c, int curr_len)
{
	int	next_len;
	int	i;
	int	j;

	i = point.i;
	j = point.j;
	next_len = 0;
	if (map[i + 1])
		next_len = ft_strlen(map[i + 1]);
	if (next_len >= curr_len)
	{
		if (map[i + 1][j] == c)
			raise_map_error(map, i, j);
	}
	else if (c == ' ' && j > next_len)
		raise_map_error(map, i, j);
}

void	check_prev_row(char **map, t_point point, char c, int curr_len)
{
	int	i;
	int	j;

	i = point.i;
	j = point.j;
	if (g_prev_len >= curr_len)
	{
		if (map[i - 1][j] == c)
			raise_map_error(map, i, j);
	}
	else if (c == ' ' && j > g_prev_len)
		raise_map_error(map, i, j);
}
