/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:40:14 by mhaddi            #+#    #+#             */
/*   Updated: 2021/04/12 02:15:21 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx-linux/mlx.h"
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
	A_KEY = 97,
	W_KEY = 119,
	S_KEY = 115,
	D_KEY = 100,
	LEFT_KEY = 65361,
	RIGHT_KEY = 65363,
	ESC_KEY = 65307
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
	int			width;
	int			height;
}				t_img_data;

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

typedef	struct	s_delta_dist {
	double		x;
	double		y;
}				t_delta_dist;

typedef struct	s_side_dist {
	double		x;
	double		y;
}				t_side_dist;

typedef struct	s_box {
	int			x;
	int			y;
}				t_box;

typedef struct	s_step {
	t_dir		dir;
}				t_step;

typedef struct	s_ray
{
	int			side;
	int			hit;
	t_dir		dir;
	t_box		box;
	t_delta_dist delta_dist;
	t_side_dist	side_dist;
	t_step		step;
	double		perp_wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	int			tex_x;
	int			tex_y;
	double		tex_step;
	double		tex_pos;
}				t_ray;

/*
typedef	struct	s_frame {
	t_ray			ray;	
	t_delta_dist 	delta_dist;
	t_side_dist		side_dist;
	int				side;
	int				hit;
	t_step			step;
}				t_frame;
*/

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
	t_pos		transform;
	int			screen_x;
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
	t_img_data		*textures;
	int				**buffer;
	t_texture_paths texture_paths;
	t_sprite		*sprites;
	int				num_sprites;
	double			*z_buffer;
	int				*sprite_order;
	double			*sprite_distance;
	int				ceiling_color;
	int				floor_color;
}					t_world;

typedef struct	s_data
{
	t_img_data	img;
	t_mlx		mlx;
	t_player	player;
	t_world		world;
	t_resolution	resolution;
	t_map_size	map_size;
	int			keystrokes[65400];
}				t_data;

void			ft_mlx_pixel_put(t_img_data *img, int x, int y, int color);
void			sort_sprites(int *order, double *dist, int amount);
void			ft_putstr_fd(char *s, int fd);

#endif
