/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 17:13:34 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/29 09:44:06 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static t_config	check_presence(t_config config)
{
	t_presence	is_present;

	is_present = config.is_present;
	if (is_present.resolution == false)
		ft_error(NULL, "Error\n Missing resolution");
	if (is_present.no_tex == false)
		ft_error(NULL, "Error\n Missing north texture");
	if (is_present.we_tex == false)
		ft_error(NULL, "Error\n Missing west texture");
	if (is_present.so_tex == false)
		ft_error(NULL, "Error\n Missing south texture");
	if (is_present.ea_tex == false)
		ft_error(NULL, "Error\n Missing east texture");
	if (is_present.sp_tex == false)
		ft_error(NULL, "Error\n Missing sprite texture");
	if (is_present.floor == false)
		ft_error(NULL, "Error\n Missing floor color");
	if (is_present.ceiling == false)
		ft_error(NULL, "Error\n Missing ceiling color");
	return (config);
}

static t_args	get_args(int c, char **v)
{
	char	*ext;
	t_args	args;

	args.is_save = false;
	if (c == 1 || c > 3)
		ft_error(NULL, "Error\ninvalid argument!");
	ext = ft_strrchr(v[1], '.');
	if (!ext)
		ft_error(NULL, "Error\ninvalid argument!");
	else if (ft_strncmp(ext, ".cub", 5) != 0)
		ft_error(NULL, "Error\ninvalid argument!");
	args.file = v[1];
	if (c == 3)
	{
		if (ft_strncmp("--save", v[2], 7) == 0)
			args.is_save = true;
		else
			ft_error(NULL, "Error\ninvalid argument!");
	}
	return (args);
}

static int	get_elements(t_config *config, int fd, char *line)
{
	char	**element;
	int		i;

	if (*line)
	{
		i = 0;
		while (line[i] == ' ')
			i++;
		if (line[i] == '1' || line[i] == '0')
		{
			config->map = parse_map(config, fd, line);
			return (1);
		}
		else
		{
			element = ft_split(line, ' ');
			if (!*element)
				ft_error(config->map, "Error\nInvalid configuration");
			check_element(config, element);
		}
	}
	return (0);
}

static t_config	init_config(t_args args)
{
	t_config	config;

	config.is_save = args.is_save;
	config.map = NULL;
	config.player = (t_player_pos){0, 0, '\0'};
	config.res = (t_resolution){0, 0};
	config.tex = (t_textures_paths){NULL, NULL, NULL, NULL, NULL};
	config.colors = (t_colors){0, 0};
	config.sprite_count = 0;
	config.is_present = (t_presence){false, false, false, false,
		false, false, false, false};
	return (config);
}

t_config	parse_file(int argc, char **argv)
{
	int			fd;
	char		*line;
	int			status;
	t_config	config;
	t_args		args;

	args = get_args(argc, argv);
	config = init_config(args);
	status = 0;
	fd = open(args.file, O_RDONLY);
	if (fd > 0)
	{
		status = get_next_line(fd, &line);
		while (status)
		{
			if (get_elements(&config, fd, line) == 1)
				return (check_presence(config));
			free(line);
			status = get_next_line(fd, &line);
		}
		ft_error(config.map, "Error\nInvalid file");
	}
	ft_error(config.map, "Error\nInvalid file\n");
	return (config);
}
