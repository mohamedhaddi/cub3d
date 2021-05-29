/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 17:12:00 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/29 10:23:12 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

t_config	check_duplicate_texture_files(t_config config)
{
	char	*no;
	char	*so;
	char	*ea;
	char	*we;

	no = config.tex.no;
	so = config.tex.so;
	ea = config.tex.ea;
	we = config.tex.we;
	if (ft_strcmp(no, ea) == 0
		|| ft_strcmp(no, so) == 0
		|| ft_strcmp(no, we) == 0
		|| ft_strcmp(ea, so) == 0
		|| ft_strcmp(ea, we) == 0
		|| ft_strcmp(so, we) == 0)
		ft_error(NULL, "Error\n Duplicate texture paths");
	return (config);
}

void	check_element(t_config *config, char **element)
{
	t_presence	*is_present;

	is_present = &config->is_present;
	if (ft_strcmp(element[0], "NO") == 0)
		config->tex.no = save_texture(element, &is_present->no_tex);
	else if (ft_strcmp(element[0], "SO") == 0)
		config->tex.so = save_texture(element, &is_present->so_tex);
	else if (ft_strcmp(element[0], "EA") == 0)
		config->tex.ea = save_texture(element, &is_present->ea_tex);
	else if (ft_strcmp(element[0], "WE") == 0)
		config->tex.we = save_texture(element, &is_present->we_tex);
	else if (ft_strcmp(element[0], "F") == 0)
		config->colors.floor = save_color(element, &is_present->floor);
	else if (ft_strcmp(element[0], "C") == 0)
		config->colors.ceiling = save_color(element, &is_present->ceiling);
	else
		ft_error(config->map, "Error\nInvalid elements");
}
