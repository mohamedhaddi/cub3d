/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 17:13:43 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/23 19:20:10 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static char	**ft_reallocate(char **old_map, int i)
{
	char	**new_map;
	int		j;

	j = 0;
	new_map = (char **)malloc((i + 1) * sizeof(char *));
	while (j < i)
	{
		new_map[j] = old_map[j];
		j++;
	}
	new_map[j] = 0;
	free(old_map);
	return (new_map);
}

char	**parse_map(t_config *config, int fd, char *line)
{
	int		i;
	int		j;
	char	**map;

	j = 1;
	i = 1;
	map = (char **)malloc((i + 1) * sizeof(char *));
	map[0] = line;
	while (j)
	{
		j = get_next_line(fd, &line);
		map[i] = line;
		i += 1;
		map = ft_reallocate(map, i);
	}
	config->rows_num = i;
	config->map = map;
	map_error(config);
	return (map);
}
