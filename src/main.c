/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 21:35:54 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 17:38:20 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <time.h>

/** calculate ray position and direction:
 *  - camera_x is x-coordinate in camera space
 */
void			set_ray_dir(int x, t_ray *ray, t_data *params)
{
	t_resolution	*resolution;
	t_player		*player;
	double			camera_x;

	resolution = &params->resolution;
	player = &params->player;
	camera_x = ((2 * x) / (double)resolution->width) - 1;
	ray->dir.x = player->dir.x + player->plane.x * camera_x;
	ray->dir.y = player->dir.y + player->plane.y * camera_x;
}

/**
 * clear buffer (by setting floor and ceiling colors)
 */
void			draw_background(t_data *params)
{
	t_world			*world;
	t_resolution	*resolution;
	int				x;
	int				y;

	world = &params->world;
	resolution = &params->resolution;
	x = 0;
	while (x < resolution->width)
	{
		y = 0;
		while (y < resolution->height)
		{
			if (y < resolution->height / 2)
				world->buffer[y][x] = world->ceiling_color;
			else
				world->buffer[y][x] = world->floor_color;
			y++;
		}
		x++;
	}
}

/**
 * what direction to step in x or y-direction (either +1 or -1)
 */
void			set_step_dir(t_ray *ray)
{
	if (ray->dir.x < 0)
		ray->step.dir.x = -1;
	else
		ray->step.dir.x = 1;
	if (ray->dir.y < 0)
		ray->step.dir.y = -1;
	else
		ray->step.dir.y = 1;
}

/**
 * calculate initial side_dist
 */
void			set_side_dist(t_ray *ray, t_player *player)
{
	if (ray->dir.x < 0)
		ray->side_dist.x = (player->pos.x - ray->box.x) * ray->delta_dist.x;
	else
		ray->side_dist.x = (ray->box.x + 1.0 - player->pos.x) * ray->delta_dist.x;
	if (ray->dir.y < 0)
		ray->side_dist.y = (player->pos.y - ray->box.y) * ray->delta_dist.y;
	else
		ray->side_dist.y = (ray->box.y + 1.0 - player->pos.y) * ray->delta_dist.y;
}

/**
 * length of ray from current position to next x or y-side
 */
void			set_delta_dist(t_ray *ray)
{
	ray->delta_dist.x = fabs(1 / ray->dir.x);
	ray->delta_dist.y = fabs(1 / ray->dir.y);
}

/**
 * which box of the map we're in
 */
void			set_ray_current_box(t_ray *ray, t_player *player)
{
	ray->box.x = (int)player->pos.x;
	ray->box.y = (int)player->pos.y;
}

/**
 * jump to next map square in x-direction
 */
void			jump_to_next_x_side(t_ray *ray)
{
	ray->side_dist.x += ray->delta_dist.x;
	ray->box.x += ray->step.dir.x;
	if (ray->dir.x > 0)
		ray->side = SO;
	else
		ray->side = NO;
}

/**
 * jump to next map square in y-direction
 */
void			jump_to_next_y_side(t_ray *ray)
{
	ray->side_dist.y += ray->delta_dist.y;
	ray->box.y += ray->step.dir.y;
	if (ray->dir.y > 0)
		ray->side = EA;
	else
		ray->side = WE;
}

/**
 * jump to next map square
 */
void			jump_to_next_square(t_ray *ray)
{
	if (ray->side_dist.x < ray->side_dist.y)
		jump_to_next_x_side(ray);
	else
		jump_to_next_y_side(ray);
}

/**
 * Check if ray has hit a wall
 */
int				is_a_wall_hit(int box)
{
	return (box == 1);
}

/**
 * perform DDA: a loop that increments the ray with 1 square every time until a wall is hit
 */
void			cast_ray(t_world *world, t_ray *ray)
{
	while (is_a_wall_hit(world->map[ray->box.x][ray->box.y]) == 0)
		jump_to_next_square(ray);
}

void			calc_ray_params(int x, t_ray *ray, t_data *params, t_player *player)
{
	set_ray_dir(x, ray, params);
	set_ray_current_box(ray, player);
	set_delta_dist(ray);
	set_step_dir(ray);
	set_side_dist(ray, player);
}

/**
 * Calculate perpendicular distance projected on camera direction (Euclidean
 * distance will give fisheye effect!)
 */
void			calc_perp_distance(t_ray *ray, t_player *player)
{
	if (ray->side % 2 == 0)
		ray->perp_wall_dist =
			(ray->box.x - player->pos.x + (1.0 - ray->step.dir.x) / 2) /
			ray->dir.x;
	else
		ray->perp_wall_dist =
			(ray->box.y - player->pos.y + (1.0 - ray->step.dir.y) / 2) /
			ray->dir.y;
}

/**
 * Calculate height of line to draw on screen
 */
void			calc_line_height(t_ray *ray, t_resolution *resolution)
{
	ray->line_height = (int)(resolution->height / ray->perp_wall_dist);
}

void			calc_first_px_of_stripe(t_ray *ray, t_resolution *resolution)
{
	ray->draw_start = -ray->line_height / 2 + resolution->height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
}

void			calc_last_px_of_stripe(t_ray *ray, t_resolution *resolution)
{
	ray->draw_end = ray->line_height / 2 + resolution->height / 2;
	if (ray->draw_end > resolution->height)
		ray->draw_end = resolution->height;
}

/**
 * calculate lowest and highest pixel to fill in current stripe
 */
void			calc_both_ends_of_vertical_stripe(t_ray *ray, t_resolution *resolution)
{
	calc_first_px_of_stripe(ray, resolution);
	calc_last_px_of_stripe(ray, resolution);
}

/**
 * calculate value of wall_x (where exactly the wall was hit)
 * The value wallX represents the exact value where the wall was hit, not just
 * the integer coordinates of the wall. This is required to know which x-coordinate
 * of the texture we have to use. This is calculated by first calculating the exact
 * x or y coordinate in the world, and then substracting the integer value of the
 * wall off it. Note that even if it's called wallX, it's actually an y-coordinate
 * of the wall if side==1, but it's always the x-coordinate of the texture.
 */
void			calc_wall_x(t_ray *ray, t_player *player)
{
	if (ray->side % 2 == 0)
		ray->wall_x = player->pos.y + ray->perp_wall_dist * ray->dir.y;
	else
		ray->wall_x = player->pos.x + ray->perp_wall_dist * ray->dir.x;
	ray->wall_x -= floor(ray->wall_x);
}

/**
 * calculate the x-coordinate on the texture
 * TEX_SIZE is width and height in texels of the textures
 */
void			calc_texture_x(t_ray *ray)
{
	ray->tex_x = (int)(ray->wall_x * (double)TEX_SIZE);
	if (ray->side % 2 == 0 && ray->dir.x > 0)
		ray->tex_x = TEX_SIZE - ray->tex_x - 1;
	if (ray->side % 2 == 1 && ray->dir.y < 0)
		ray->tex_x = TEX_SIZE - ray->tex_x - 1;
}

/**
 * set how much to increase the texture coordinate per screen pixel
 */
void			set_texture_coordinate_step(t_ray *ray)
{
	ray->tex_step = 1.0 * TEX_SIZE / ray->line_height;
}

/**
 * set starting texture coordinate
 */
void			set_starting_texture_coordinate(t_ray *ray, t_resolution *resolution)
{
	ray->tex_pos =
		(ray->draw_start - resolution->height / 2.0 + ray->line_height / 2.0) *
		ray->tex_step;
}

/**
 * draw a vertical stripe of a wall:
 * - `ray->tex_y = ...` -> Cast the texture coordinate to integer, and mask with
 * (TEX_SIZE - 1) in case of overflow
 * - `if ((color & 0x00FFFFFF) != 0) ...` -> paint pixel if it isn't black,
 * black is the invisible color
 * - y-coordinate is first in buffer because it works per scanline
 */
void			draw_wall_vertical_stripe(int x, t_ray *ray, t_world *world)
{
	int	y;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		ray->tex_y = (int)ray->tex_pos & (TEX_SIZE - 1);
		ray->tex_pos += ray->tex_step;
		int color =
			world->textures[ray->side].addr[TEX_SIZE * ray->tex_y + ray->tex_x];
		if ((color & 0x00FFFFFF) != 0)
			world->buffer[y][x] = color;
		y++;
	}
}

/**
 * SET THE ZBUFFER FOR THE SPRITE CASTING
 */
void			set_zbuffer(int x, t_ray *ray, t_world *world)
{
	world->z_buffer[x] = ray->perp_wall_dist; // perpendicular distance is used
}

/**
 * WALL CASTING LOOP
 */
void			cast_walls(t_resolution *resolution,
				t_player *player,
				t_world *world,
				t_data *params)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < resolution->width)
	{
		calc_ray_params(x, &ray, params, player);
		cast_ray(world, &ray);
		calc_perp_distance(&ray, player);
		calc_line_height(&ray, resolution);
		calc_both_ends_of_vertical_stripe(&ray, resolution);
		calc_wall_x(&ray, player);
		calc_texture_x(&ray);
		set_texture_coordinate_step(&ray);
		set_starting_texture_coordinate(&ray, resolution);
		draw_wall_vertical_stripe(x, &ray, world);
		set_zbuffer(x, &ray, world);
		x++;
	}
}

/**
 * sort sprites from far to close
 */
void			set_sprites_distance(t_world *world, t_player *player)
{
	int	i;

	i = 0;
	while (i < world->num_sprites)
	{
		world->sprite_order[i] = i;
		world->sprite_distance[i] =
			((player->pos.x - world->sprites[i].pos.x) *
					(player->pos.x - world->sprites[i].pos.x) +
				(player->pos.y - world->sprites[i].pos.y) *
					(player->pos.y - world->sprites[i].pos.y));
		i++;
	}
}

/**
 * translate sprite position to relative to camera
 */
void			make_sprite_pos_relative_to_camera(int sprite_num,
										t_sprite *sprite,
										t_world *world,
										t_player *player)
{
	sprite->pos.x =
		world->sprites[world->sprite_order[sprite_num]].pos.x - player->pos.x;
	sprite->pos.y =
		world->sprites[world->sprite_order[sprite_num]].pos.y - player->pos.y;
}

/**
 * transform sprite with the inverse camera matrix
 * [planeX dirX] -1                                 [dirY     -dirX]
 * [           ]    = 1/(planeX*dirY-dirX*planeY) * [              ]
 * [planeY dirY]                                    [-planeY planeX]
 * - `inv_det` required for correct matrix multiplication
 * - `sprite->transform.y` is actually the depth inside the screen, that what z is in 3D
 */
void			transform_sprite_with_inverse_camera_matrix(t_sprite *sprite,
													t_resolution *resolution,
													t_player *player)
{
	double inv_det = 1.0 /
		(player->plane.x * player->dir.y - player->dir.x * player->plane.y);
	sprite->transform.x = inv_det *
		(player->dir.y * sprite->pos.x - player->dir.x * sprite->pos.y);
	sprite->transform.y = inv_det *
		(-player->plane.y * sprite->pos.x + player->plane.x * sprite->pos.y);
	sprite->screen_x = (int)(((double)resolution->width / 2) *
								(1 + sprite->transform.x / sprite->transform.y));
}

/**
 * calculate height of the sprite on screen
 * using 'transform_y' instead of the real distance prevents fisheye
 */
void			calc_sprite_height(t_sprite *sprite, t_resolution *resolution)
{
	sprite->height = abs((int)(resolution->height / sprite->transform.y));
}

/**
 * calculate lowest and highest pixel to fill in current stripe
 */
void			calc_start_end_of_stripe(t_sprite *sprite, t_resolution *resolution)
{
	sprite->draw_start_y = -sprite->height / 2 + resolution->height / 2;
	if (sprite->draw_start_y < 0)
		sprite->draw_start_y = 0;
	sprite->draw_end_y = sprite->height / 2 + resolution->height / 2;
	if (sprite->draw_end_y >= resolution->height)
		sprite->draw_end_y = resolution->height;
}

/**
 * calculate width of the sprite
 */
void			calc_sprite_width(t_sprite *sprite, t_resolution *resolution)
{
	sprite->width = abs((int)(resolution->height / sprite->transform.y));
	sprite->draw_start_x = -sprite->width / 2 + sprite->screen_x;
	if (sprite->draw_start_x < 0)
		sprite->draw_start_x = 0;
	sprite->draw_end_x = sprite->width / 2 + sprite->screen_x;
	if (sprite->draw_end_x >= resolution->width)
		sprite->draw_end_x = resolution->width;
}

/**
 * - 256 and 128 factors to avoid floats
 * - `color` -> gets current color from the sprite texture
 * - `if ((color & 0x00FFFFFF) != 0) ...` -> paint pixel if it isn't black,
 * black is the invisible color
 */
void			draw_sprite_vertical_stripe(int stripe,
									int tex_x,
									t_sprite *sprite,
									t_data *params)
{
	t_world			*world;
	t_resolution	*resolution;
	int				y;
	int				d;
	int				tex_y;
	int				color;

	world = &params->world;
	resolution = &params->resolution;
	y = sprite->draw_start_y;
	while (y < sprite->draw_end_y)
	{
		d = (y)*256 - resolution->height * 128 + sprite->height * 128;
		tex_y = ((d * TEX_SIZE) / sprite->height) / 256;
		color = world->textures[SPRITE_INDEX].addr[TEX_SIZE * tex_y + tex_x];
		if ((color & 0x00FFFFFF) != 0)
			world->buffer[y][stripe] = color;
		y++;
	}
}

/**
 * loop through every vertical stripe of the sprite on screen
 * the conditions in the if are:
 * 1) it's in front of camera plane so you don't see things behind you
 * 2) it's on the screen (left)
 * 3) it's on the screen (right)
 * 4) z_buffer, with perpendicular distance
 */
void			loop_through_sprite_stripes(t_sprite *sprite,
									t_resolution *resolution,
									t_world *world,
									t_data *params)
{
	int	stripe;

	stripe = sprite->draw_start_x;
	while (stripe < sprite->draw_end_x)
	{
		int tex_x =
			(int)(256 * (stripe - (-sprite->width / 2 + sprite->screen_x)) *
					TEX_SIZE / sprite->width) /
			256;
		if (sprite->transform.y > 0 && stripe > 0 && stripe < resolution->width &&
			sprite->transform.y < world->z_buffer[stripe])
			draw_sprite_vertical_stripe(stripe, tex_x, sprite, params);
		stripe++;
	}
}

/**
 * after sorting the sprites, do the projection and draw them
 */
void			draw_sprites(t_world *world,
					t_player *player,
					t_resolution *resolution,
					t_data *params)
{
	t_sprite	sprite;
	int			i;

	i = 0;
	while (i < world->num_sprites)
	{
		make_sprite_pos_relative_to_camera(i, &sprite, world, player);
		transform_sprite_with_inverse_camera_matrix(&sprite, resolution, player);
		calc_sprite_height(&sprite, resolution);
		calc_start_end_of_stripe(&sprite, resolution);
		calc_sprite_width(&sprite, resolution);
		loop_through_sprite_stripes(&sprite, resolution, world, params);
		i++;
	}
}

void			draw_buffer(t_resolution *resolution,
					t_world *world,
					t_img_data *img,
					t_mlx *mlx)
{
	int	x;
	int	y;

	x = 0;
	while (x < resolution->width)
	{
		y = 0;
		while (y < resolution->height)
		{
			ft_mlx_pixel_put(img, x, y, world->buffer[y][x]);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win, img->img, 0, 0);
}

void			cast_sprites(t_world *world,
					t_player *player,
					t_resolution *resolution,
					t_data *params)
{
	set_sprites_distance(world, player);
	sort_sprites(world->sprite_order, world->sprite_distance, world->num_sprites);
	draw_sprites(world, player, resolution, params);
}

/**
 * this is the function that draws a whole frame every time a control key is pressed
 */
int				draw_frame(t_data *params)
{
	t_mlx			*mlx;
	t_img_data		*img;
	t_player		*player;
	t_world			*world;
	t_resolution	*resolution;

	mlx = &params->mlx;
	img = &params->img;
	player = &params->player;
	world = &params->world;
	resolution = &params->resolution;
	draw_background(params);
	cast_walls(resolution, player, world, params);
	cast_sprites(world, player, resolution, params);
	draw_buffer(resolution, world, img, mlx);
	print_info(player, params);
	return (0);
}

/**
 * move forward if no wall in front of you
 * - `if (...) ...` -> collision detection: won't move if it ain't 0 (a wall)
 */
void			move_forward(t_data *params)
{
	t_player	*player;
	t_world		*world;

	player = &params->player;
	world = &params->world;
	if (world->map[(int)(player->pos.x + player->dir.x * player->speed.move_speed)]
					[(int)(player->pos.y)] %
			2 ==
		0)
		player->pos.x += player->dir.x * player->speed.move_speed;
	if (world->map[(int)(player->pos.x)][(
			int)(player->pos.y + player->dir.y * player->speed.move_speed)] %
			2 ==
		0)
		player->pos.y += player->dir.y * player->speed.move_speed;
}

/**
 * move backwards if no wall behind you
 * - `if (...) ...` -> collision detection: won't move if it ain't 0 (a wall)
 */
void			move_backward(t_data *params)
{
	t_player	*player;
	t_world		*world;

	player = &params->player;
	world = &params->world;
	if (world->map[(int)(player->pos.x - player->dir.x * player->speed.move_speed)]
					[(int)(player->pos.y)] %
			2 ==
		0)
		player->pos.x -= player->dir.x * player->speed.move_speed;
	if (world->map[(int)(player->pos.x)][(
			int)(player->pos.y - player->dir.y * player->speed.move_speed)] %
			2 ==
		0)
		player->pos.y -= player->dir.y * player->speed.move_speed;
}

/**
 * move to the right if no wall is on the right
 * - `if (...) ...` -> collision detection: won't move if it ain't 0 (a wall)
 */
void			move_right(t_data *params)
{
	t_player	*player;
	t_world		*world;

	player = &params->player;
	world = &params->world;
	if (world->map[(int)(player->pos.x + player->plane.x * player->speed.move_speed)]
					[(int)(player->pos.y)] %
			2 ==
		0)
		player->pos.x += player->plane.x * player->speed.move_speed;
	if (world->map[(int)(player->pos.x)][(
			int)(player->pos.y + player->plane.y * player->speed.move_speed)] %
			2 ==
		0)
		player->pos.y += player->plane.y * player->speed.move_speed;
}

/**
 * move to the left if no wall is on the left
 * - `if (...) ...` -> collision detection: won't move if it ain't 0 (a wall)
 */
void			move_left(t_data *params)
{
	t_player	*player;
	t_world		*world;

	player = &params->player;
	world = &params->world;
	if (world->map[(int)(player->pos.x - player->plane.x * player->speed.move_speed)]
					[(int)(player->pos.y)] %
			2 ==
		0)
		player->pos.x -= player->plane.x * player->speed.move_speed;
	if (world->map[(int)(player->pos.x)][(
			int)(player->pos.y - player->plane.y * player->speed.move_speed)] %
			2 ==
		0)
		player->pos.y -= player->plane.y * player->speed.move_speed;
}

/**
 * rotate to the right:
 * - both camera direction and camera plane must be rotated
 */
void			rotate_right(t_data *params)
{
	double		old_dir_x;
	double		old_plane_x;
	t_player	*player;
	t_world		*world;

	player = &params->player;
	world = &params->world;
	old_dir_x = player->dir.x;
	player->dir.x = player->dir.x * cos(-player->speed.rot_speed) -
		player->dir.y * sin(-player->speed.rot_speed);
	player->dir.y = old_dir_x * sin(-player->speed.rot_speed) +
		player->dir.y * cos(-player->speed.rot_speed);
	old_plane_x = player->plane.x;
	player->plane.x = player->plane.x * cos(-player->speed.rot_speed) -
		player->plane.y * sin(-player->speed.rot_speed);
	player->plane.y = old_plane_x * sin(-player->speed.rot_speed) +
		player->plane.y * cos(-player->speed.rot_speed);
}

/**
 * rotate to the left:
 * - both camera direction and camera plane must be rotated
 */
void			rotate_left(t_data *params)
{
	double		old_dir_x;
	double		old_plane_x;
	t_player	*player;
	t_world		*world;

	player = &params->player;
	world = &params->world;
	old_dir_x = player->dir.x;
	player->dir.x = player->dir.x * cos(player->speed.rot_speed) -
		player->dir.y * sin(player->speed.rot_speed);
	player->dir.y = old_dir_x * sin(player->speed.rot_speed) +
		player->dir.y * cos(player->speed.rot_speed);
	old_plane_x = player->plane.x;
	player->plane.x = player->plane.x * cos(player->speed.rot_speed) -
		player->plane.y * sin(player->speed.rot_speed);
	player->plane.y = old_plane_x * sin(player->speed.rot_speed) +
		player->plane.y * cos(player->speed.rot_speed);
}

int				read_keys(t_data *params)
{
	if (params->keystrokes[W_KEY])
		move_forward(params);
	if (params->keystrokes[S_KEY])
		move_backward(params);
	if (params->keystrokes[D_KEY])
		move_right(params);
	if (params->keystrokes[A_KEY])
		move_left(params);
	if (params->keystrokes[RIGHT_KEY])
		rotate_right(params);
	if (params->keystrokes[LEFT_KEY])
		rotate_left(params);
	if (params->keystrokes[ESC_KEY])
		exit_game(params, EXIT_SUCCESS);
	draw_frame(params);
	return (0);
}

int				is_control_key(int keycode)
{
	return (keycode == LEFT_KEY || keycode == RIGHT_KEY || keycode == W_KEY ||
			keycode == S_KEY || keycode == A_KEY || keycode == D_KEY ||
			keycode == ESC_KEY);
}

int				key_press(int keycode, t_data *params)
{
	if (is_control_key(keycode))
		params->keystrokes[keycode] = 1;
	return (0);
}

int				key_release(int keycode, t_data *params)
{
	if (is_control_key(keycode))
		params->keystrokes[keycode] = 0;
	return (0);
}

int				main()
{
	t_data		params;
	t_mlx		*mlx;
	t_img_data	*img;

	mlx = &params.mlx;
	img = &params.img;
	srand(time(NULL));
	alloc_strings();
	set_screen_resolution(&params);
	set_map_size(&params);
	generate_world_map(&params);
	load_mlx(&params);
	load_game(&params);
	draw_frame(&params);
	mlx_loop_hook(mlx->ptr, read_keys, &params);
	mlx_hook(mlx->win, 2, 1L, key_press, &params);
	mlx_hook(mlx->win, 3, 2L, key_release, &params);
	mlx_hook(mlx->win, 17, 1L, red_cross_press, &params);
	mlx_loop(mlx->ptr);
}
