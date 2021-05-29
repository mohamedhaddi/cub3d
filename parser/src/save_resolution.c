/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_resolution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 17:14:14 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/23 19:23:33 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static int	check_resolution_error(char **resolution, int i)
{
	int	j;

	if (i > 2)
	{
		free_double_pointer(resolution);
		return (1);
	}
	j = 0;
	while (resolution[i][j])
	{
		if (resolution[i][j] < '0' || resolution[i][j] > '9')
		{
			free_double_pointer(resolution);
			return (1);
		}
		j++;
	}
	return (0);
}

static int	get_width(char *resolution)
{
	int	width;

	width = ft_atoi(resolution);
	if (width > 2560)
		width = 2560;
	if (width < 0)
		ft_error(NULL, "Error\nIncorrect resolution");
	return (width);
}

static int	get_height(char *resolution)
{
	int	height;

	height = ft_atoi(resolution);
	if (height > 1440)
		height = 1440;
	if (height < 0)
		ft_error(NULL, "Error\nIncorrect resolution");
	return (height);
}

t_resolution	save_resolution(char **resolution, bool *presence)
{
	t_resolution	res;
	static int		res_count;
	int				i;

	if (res_count > 0)
		ft_error(NULL, "Error\n Duplicated resolution");
	res_count++;
	i = 1;
	while (resolution[i])
	{
		if (check_resolution_error(resolution, i))
			ft_error(NULL, "Error\nResolution is invalid");
		if (i == 1)
			res.width = get_width(resolution[1]);
		else if (i == 2)
			res.height = get_height(resolution[2]);
		i++;
	}
	free_double_pointer(resolution);
	if (i != 3)
		ft_error(NULL, "Error\nResolution is invalid");
	*presence = true;
	return (res);
}
