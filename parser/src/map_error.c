/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 17:13:18 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/21 17:13:19 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static void		check_surrounding(char **map, int i, int j, char c)
{
	int	curr_len;

	curr_len = ft_strlen(map[i]);
	if (j > 0 && map[i][j - 1] == c)
		raise_map_error(map, i, j);
	if (j <= curr_len)
		if (map[i][j + 1] == c)
			raise_map_error(map, i, j);
	if (map[i][j + 1] == '\0')
		raise_map_error(map, i, j);
	if (j >= g_prev_len && i != 0 && map[i][j] != ' ')
		raise_map_error(map, i, j);
	if (j == 0 && map[i][j] != ' ')
		raise_map_error(map, i, j);
	check_next_row(map, (t_point){i, j}, c, curr_len);
	check_prev_row(map, (t_point){i, j}, c, curr_len);
}

static void		check_error(char **map, int i, int j)
{
	if (map[i][j] != '1')
	{
		if (map[i][j] != ' ')
			check_surrounding(map, i, j, ' ');
		else
		{
			check_surrounding(map, i, j, '0');
			check_surrounding(map, i, j, '2');
		}
	}
}

void			map_error(t_config *config)
{
	char	**map;
	int		i;
	int		j;

	map = config->map;
	i = 0;
	while (map[i])
	{
		j = 0;
		if (map[i][j] == '\0')
			raise_map_error(map, i, j);
		while (map[i][j])
		{
			check_if_valid(config, i, j);
			check_error(map, i, j);
			j++;
		}
		g_prev_len = j;
		i++;
	}
	if (g_player_num == 0)
		ft_error(map, "Error\nPlayer does not exist");
}
