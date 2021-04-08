/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:40:14 by mhaddi            #+#    #+#             */
/*   Updated: 2021/04/08 16:13:15 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define TEX_SIZE 64
# define SPRITE_INDEX 4

enum			e_directions
{
	NO,
	EA,
	SO,
	WE
};

enum			e_keycodes
{
	W_KEY = 13,
	S_KEY = 1,
	D_KEY = 2,
	A_KEY = 0,
	RIGHT_KEY = 124,
	LEFT_KEY = 123,
	ESC_KEY = 53
};

typedef struct	s_resolution {
	int			width;
	int			height;
} 				t_resolution;

typedef struct	e_map_size {
	int			width;
	int			height;
}				t_map_size;

typedef struct	s_img_data
{
	void		*img;
	int			*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img_data;

typedef struct	s_texture
{
	t_img_data	texture_img_data;
	int			width;
	int			height;
}				t_texture;

typedef struct	s_mlx
{
	void		*ptr;
	void		*win;
}				t_mlx;

typedef	struct	s_pos {
	double		x;
	double		y;
}				t_pos;

typedef	struct	s_dir {
	double		x;
	double		y;
}				t_dir;

typedef	struct	s_plane {
	double		x;
	double		y;
}				t_plane;

typedef	struct	s_speed {
	double		move_speed;
	double		rot_speed;
}				t_speed;

typedef struct	s_player
{
	t_pos		pos;
	t_dir		dir;
	t_plane		plane;
	t_speed		speed;
}				t_player;

typedef struct	s_sprite
{
	t_pos		pos;
}				t_sprite;

typedef struct	s_pair
{
	double		first;
	int			second;
}				t_pair;

typedef	struct	s_texture_paths
{
	char		*walls_facing_north;
	char		*walls_facing_south;
	char		*walls_facing_east;
	char		*walls_facing_west;
	char		*sprite;
}				t_texture_paths;

typedef struct	s_world
{
	int				**map;
	t_texture		textures[7];
	int				**buffer;
	t_texture_paths texture_paths;
	t_sprite		*sprites;
	int				num_sprites;
	double			*z_buffer;
	int				*sprite_order;
	double			*sprite_distance;
}					t_world;

typedef struct	s_data
{
	t_img_data	img;
	t_mlx		mlx;
	t_player	player;
	t_world		world;
	t_resolution	resolution;
	t_map_size	map_size;
	int			keystrokes[127];
}				t_data;

void			ft_mlx_pixel_put(t_img_data *img, int x, int y, int color);
void			sort_sprites(int *order, double *dist, int amount);
void			ft_putstr_fd(char *s, int fd);

#endif
