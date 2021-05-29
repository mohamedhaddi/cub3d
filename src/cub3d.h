/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:40:14 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/25 04:33:26 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "../parser/parser.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define TEX_SIZE 64
# define TEX_NUM 4

enum				e_squares
{
	FLOOR,
	WALL
};

enum				e_directions
{
	NO,
	EA,
	SO,
	WE
};

enum				e_keycodes
{
	W_KEY = 13,
	S_KEY = 1,
	D_KEY = 2,
	A_KEY = 0,
	RIGHT_KEY = 124,
	LEFT_KEY = 123,
	ESC_KEY = 53
};

typedef struct s_map_size
{
	int				width;
	int				height;
}					t_map_size;

typedef struct s_img_data
{
	void			*img;
	int				*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
}					t_img_data;

typedef struct s_mlx
{
	void			*ptr;
	void			*win;
}					t_mlx;

typedef struct s_pos
{
	double			x;
	double			y;
}					t_pos;

typedef struct s_dir
{
	double			x;
	double			y;
}					t_dir;

typedef struct s_plane
{
	double			x;
	double			y;
}					t_plane;

typedef struct s_delta_dist
{
	double			x;
	double			y;
}					t_delta_dist;

typedef struct s_side_dist
{
	double			x;
	double			y;
}					t_side_dist;

typedef struct s_box
{
	int				x;
	int				y;
}					t_box;

typedef struct s_step
{
	t_dir			dir;
}					t_step;

typedef struct s_ray
{
	int				side;
	int				hit;
	t_dir			dir;
	t_box			box;
	t_delta_dist	delta_dist;
	t_side_dist		side_dist;
	t_step			step;
	double			perp_wall_dist;
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			wall_x;
	int				tex_x;
	int				tex_y;
	double			tex_step;
	double			tex_pos;
}					t_ray;

typedef struct s_speed
{
	double			move_speed;
	double			rot_speed;
}					t_speed;

typedef struct s_player
{
	t_pos			pos;
	t_dir			dir;
	t_plane			plane;
	t_speed			speed;
}					t_player;

typedef struct s_pair
{
	double			first;
	int				second;
}					t_pair;

typedef struct s_texture_paths
{
	char			*walls_facing_north;
	char			*walls_facing_south;
	char			*walls_facing_east;
	char			*walls_facing_west;
}					t_texture_paths;

typedef struct s_world
{
	char			**map;
	t_img_data		*textures;
	int				**buffer;
	t_texture_paths	texture_paths;
	int				ceiling_color;
	int				floor_color;
}					t_world;

typedef struct s_resolution
{
	int				height;
	int				width;
}					t_resolution;

typedef struct s_data
{
	t_img_data		img;
	t_mlx			mlx;
	t_player		player;
	t_world			world;
	t_resolution	resolution;
	t_map_size		map_size;
	int				keystrokes[127];
}					t_data;

void				ft_mlx_pixel_put(t_img_data *img, int x, int y, int color);
void				ft_putstr_fd(char *s, int fd);
void				exit_game(t_data *params, int status);
int					red_cross_press(t_data *params);
void				load_mlx(t_data *params);
void				set_screen_resolution(t_data *params);
void				load_game(t_data *params, int argc, char **argv);
void				spawn_player(t_data *params, t_config *config);
void				set_player_speed(t_player *player);
void				set_texture_paths(t_world *world, t_config *config);
void				set_background_colors(t_world *world, t_config *config);
void				setup_buffers(t_data *params);
void				setup_sprites(t_data *params, t_config *config);
void				load_textures(t_data *params);
void				initiliaze_keystrokes(int *keystrokes);
int					key_release(int keycode, t_data *params);
int					key_press(int keycode, t_data *params);
int					read_keys(t_data *params);
void				rotate_left(t_data *params);
void				rotate_right(t_data *params);
void				move_left(t_data *params);
void				move_right(t_data *params);
void				move_backward(t_data *params);
void				move_forward(t_data *params);
int					draw_frame(t_data *params);
void				sort_sprites(int *order, double *dist, int amount);
void				cast_sprites(t_world *world,
						t_player *player,
						t_resolution *resolution,
						t_data *params);
void				draw_buffer(t_resolution *resolution,
						t_world *world,
						t_img_data *img,
						t_mlx *mlx);
void				draw_sprites(t_world *world,
						t_player *player,
						t_resolution *resolution,
						t_data *params);
void				loop_through_sprite_stripes(t_sprite *sprite,
						t_resolution *resolution,
						t_world *world,
						t_data *params);
void				calc_sprite_width(t_sprite *sprite,
						t_resolution *resolution);
void				calc_start_end_of_stripe(t_sprite *sprite,
						t_resolution *resolution);
void				calc_sprite_height(t_sprite *sprite,
						t_resolution *resolution);
void				transform_sprite_with_inverse_camera_matrix(
						t_sprite *sprite,
						t_resolution *resolution,
						t_player *player);
void				make_sprite_pos_relative_to_camera(int sprite_num,
						t_sprite *sprite,
						t_world *world,
						t_player *player);
void				set_sprites_distance(t_world *world, t_player *player);
void				cast_walls(t_resolution *resolution,
						t_player *player,
						t_world *world,
						t_data *params);
void				draw_wall_vertical_stripe(int x, t_ray *ray,
						t_world *world);
void				set_starting_texture_coordinate(t_ray *ray,
						t_resolution *resolution);
void				set_texture_coordinate_step(t_ray *ray);
void				calc_texture_x(t_ray *ray);
void				calc_wall_x(t_ray *ray, t_player *player);
void				calc_both_ends_of_vertical_stripe(t_ray *ray,
						t_resolution *resolution);
void				calc_line_height(t_ray *ray, t_resolution *resolution);
void				calc_perp_distance(t_ray *ray, t_player *player);
void				calc_ray_params(int x, t_ray *ray,
						t_data *params, t_player *player);
void				cast_ray(t_world *world, t_ray *ray);
void				set_ray_current_box(t_ray *ray, t_player *player);
void				set_delta_dist(t_ray *ray);
void				set_side_dist(t_ray *ray, t_player *player);
void				set_step_dir(t_ray *ray);
void				draw_background(t_data *params);
void				set_ray_dir(int x, t_ray *ray, t_data *params);
void				set_world_map(t_data *params, t_config *config);
void				take_screenshot(t_data *params);

#endif
