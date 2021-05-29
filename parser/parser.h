/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 17:11:17 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/29 10:22:41 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "../libft/libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_args
{
	char	*file;
}				t_args;

typedef struct s_textures_paths
{
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
}				t_textures_paths;

typedef struct s_colors
{
	int	ceiling;
	int	floor;
}				t_colors;

typedef struct s_player_pos
{
	double	pos_x;
	double	pos_y;
	char	dir;
}				t_player_pos;

typedef struct s_coordinate
{
	double	x;
	double	y;
}				t_coordinate;

typedef struct s_presence
{
	bool	no_tex;
	bool	we_tex;
	bool	so_tex;
	bool	ea_tex;
	bool	floor;
	bool	ceiling;
}				t_presence;

typedef struct s_config
{
	char				**map;
	int					rows_num;
	t_textures_paths	tex;
	t_colors			colors;
	t_player_pos		player;
	t_presence			is_present;
	int					g_prev_len;
	size_t				g_player_num;
}				t_config;

typedef struct s_point
{
	int	i;
	int	j;
}				t_point;

t_config		parse_file(int argc, char **argv);
void			ft_error(char **map, char *error);
void			raise_map_error(char **map, int i, int j);
void			check_element(t_config *config, char **element);
t_resolution	save_resolution(char **resolution, bool *presence);
int				save_color(char **element, bool *presence);
char			*save_texture(char **texture, bool *presence);
char			**parse_map(t_config *config, int fd, char *line);
void			free_double_pointer(char **ptr);
void			map_error(t_config *config);
void			check_if_valid(t_config *config, int i, int j);
int				is_player(t_config *config, int i, int j);
int				is_sprite(t_config *config, int i, int j);
void			check_next_row(t_config *config,
					t_point point,
					char c,
					int curr_len);
void			check_prev_row(t_config *config,
					t_point point,
					char c,
					int curr_len);
int				free_memory(char **map, int status);
t_config		check_duplicate_texture_files(t_config config);
#endif
