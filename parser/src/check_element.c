/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 17:12:00 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/21 17:12:03 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void		check_element(t_config *config, char **element)
{
	t_presence *is_present;

	is_present = &config->is_present;
	if (ft_strcmp(element[0], "R") == 0)
		config->res = save_resolution(element, &is_present->resolution);
	else if (ft_strcmp(element[0], "NO") == 0)
		config->tex.no = save_texture(element, &is_present->no_tex);
	else if (ft_strcmp(element[0], "SO") == 0)
		config->tex.so = save_texture(element, &is_present->so_tex);
	else if (ft_strcmp(element[0], "EA") == 0)
		config->tex.ea = save_texture(element, &is_present->ea_tex);
	else if (ft_strcmp(element[0], "WE") == 0)
		config->tex.we = save_texture(element, &is_present->we_tex);
	else if (ft_strcmp(element[0], "S") == 0)
		config->tex.sp = save_texture(element, &is_present->sp_tex);
	else if (ft_strcmp(element[0], "F") == 0)
		config->colors.floor = save_color(element, &is_present->floor);
	else if (ft_strcmp(element[0], "C") == 0)
		config->colors.ceiling = save_color(element, &is_present->ceiling);
	else
		ft_error(config->map, "Error\nInvalid elements");
}
