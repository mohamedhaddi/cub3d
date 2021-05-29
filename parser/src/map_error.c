/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 17:13:18 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/29 09:28:06 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static void	check_surrounding(t_config *config, int i, int j, char c)
{
	int		curr_len;
	char	**map;

	map = config->map;
	curr_len = ft_strlen(map[i]);
	if (j > 0 && map[i][j - 1] == c)
		raise_map_error(map, i, j);
	if (j <= curr_len)
		if (map[i][j + 1] == c)
			raise_map_error(map, i, j);
	if (map[i][j + 1] == '\0')
		raise_map_error(map, i, j);
	if (j >= config->g_prev_len && i != 0 && map[i][j] != ' ')
		raise_map_error(map, i, j);
	if (j == 0 && map[i][j] != ' ')
		raise_map_error(map, i, j);
	check_next_row(config, (t_point){i, j}, c, curr_len);
	check_prev_row(config, (t_point){i, j}, c, curr_len);
}

static void	check_error(t_config *config, int i, int j)
{
	char	**map;

	map = config->map;
	if (map[i][j] != '1')
	{
		if (map[i][j] != ' ')
			check_surrounding(config, i, j, ' ');
		else
			check_surrounding(config, i, j, '0');
	}
}

char	*rstrip_space(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	i--;
	while (i)
	{
		if (s[i] == ' ')
		{
			s[i] = '\0';
			i--;
		}
		else
			break ;
	}
	return (s);
}

void	map_error(t_config *config)
{
	char	**map;
	int		i;
	int		j;

	map = config->map;
	i = 0;
	while (map[i])
	{
		map[i] = rstrip_space(map[i]);
		j = 0;
		if (map[i][j] == '\0')
			raise_map_error(map, i, j);
		while (map[i][j])
		{
			check_if_valid(config, i, j);
			check_error(config, i, j);
			j++;
		}
		config->g_prev_len = j;
		i++;
	}
	if (config->g_player_num == 0)
		ft_error(map, "Error\nPlayer does not exist");
}
