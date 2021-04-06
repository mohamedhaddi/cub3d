/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:40:14 by mhaddi            #+#    #+#             */
/*   Updated: 2021/04/06 17:53:07 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define screen_width 640
# define screen_height 480
# define map_width 24
# define map_height 24
# define tex_size 64

enum			e_directions
{
	NO,
	EA,
	SO,
	WE
};

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

typedef struct	s_player
{
	double		dir_x;
	double		dir_y;
	double		pos_x;
	double		pos_y;
	double		plane_x;
	double		plane_y;
	double		move_speed;
	double		rot_speed;
}				t_player;

typedef struct	s_sprite
{
	double		x;
	double		y;
}				t_sprite;

typedef struct	s_pair
{
	double		first;
	int			second;
}				t_pair;

typedef struct	s_world
{
	t_texture	textures[7];
	int			buffer[screen_height][screen_width];
	t_sprite	*sprites;
	int			num_sprites;
	double		z_buffer[screen_width];
	int			*sprite_order;
	double		*sprite_distance;
}				t_world;

typedef struct	s_data
{
	t_img_data	img;
	t_mlx		mlx;
	t_player	player;
	t_world		world;
	int			keystrokes[127];
}				t_data;

void			ft_mlx_pixel_put(t_img_data *img, int x, int y, int color);

void			sort_sprites(int *order, double *dist, int amount);

#endif
