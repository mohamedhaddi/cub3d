/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 21:35:54 by mhaddi            #+#    #+#             */
/*   Updated: 2021/04/10 19:22:12 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include "cub3d.h"

void print_info(t_player *player, t_data *params) {
	char		*output_pos_x;
	char		*output_pos_y;
	char		*output_dir_x;
	char		*output_dir_y;
	char		*output_keystrokes_f;
	char		*output_keystrokes_b;
	char		*output_keystrokes_r;
	char		*output_keystrokes_l;
	char		*output_keystrokes_d;
	char		*output_keystrokes_a;

	t_mlx *mlx = &params->mlx;
	// show real-time values for cetain variables on screen
	output_pos_x = (char *)malloc(20 * sizeof(char));
	output_pos_y = (char *)malloc(20 * sizeof(char));
	output_dir_x = (char *)malloc(20 * sizeof(char));
	output_dir_y = (char *)malloc(20 * sizeof(char));
	output_keystrokes_f = (char *)malloc(20 * sizeof(char));
	output_keystrokes_b = (char *)malloc(20 * sizeof(char));
	output_keystrokes_r = (char *)malloc(20 * sizeof(char));
	output_keystrokes_l = (char *)malloc(20 * sizeof(char));
	output_keystrokes_d = (char *)malloc(20 * sizeof(char));
	output_keystrokes_a = (char *)malloc(20 * sizeof(char));
	sprintf(output_pos_x, "pos_x: %f", player->pos.x);
	sprintf(output_pos_y, "pos_y: %f", player->pos.y);
	sprintf(output_dir_x, "dir_x: %f", player->dir.x);
	sprintf(output_dir_y, "dir_y: %f", player->dir.y);
	sprintf(output_keystrokes_f, "key_w: %d", params->keystrokes[13]);
	sprintf(output_keystrokes_b, "key_s: %d", params->keystrokes[1]);
	sprintf(output_keystrokes_r, "key_r: %d", params->keystrokes[124]);
	sprintf(output_keystrokes_l, "key_l: %d", params->keystrokes[123]);
	sprintf(output_keystrokes_d, "key_d: %d", params->keystrokes[2]);
	sprintf(output_keystrokes_a, "key_a: %d", params->keystrokes[0]);
	mlx_string_put(mlx->ptr, mlx->win, 0, 0, 0x00FFFFFF, output_pos_x);
	mlx_string_put(mlx->ptr, mlx->win, 0, 20, 0x00FFFFFF, output_pos_y);
	mlx_string_put(mlx->ptr, mlx->win, 0, 40, 0x00FFFFFF, output_dir_x);
	mlx_string_put(mlx->ptr, mlx->win, 0, 60, 0x00FFFFFF, output_dir_y);
	mlx_string_put(mlx->ptr, mlx->win, 0, 80, 0x00FFFFFF, output_keystrokes_f);
	mlx_string_put(mlx->ptr, mlx->win, 0, 100, 0x00FFFFFF, output_keystrokes_b);
	mlx_string_put(mlx->ptr, mlx->win, 0, 120, 0x00FFFFFF, output_keystrokes_r);
	mlx_string_put(mlx->ptr, mlx->win, 0, 140, 0x00FFFFFF, output_keystrokes_l);
	mlx_string_put(mlx->ptr, mlx->win, 0, 160, 0x00FFFFFF, output_keystrokes_d);
	mlx_string_put(mlx->ptr, mlx->win, 0, 180, 0x00FFFFFF, output_keystrokes_a);
}

/**
 * test
 */

void		exit_game(t_data *params, int status)
{
	int	i;

	/*
	i = 0;
	while (game->world->map[i])
	{
		free(game->world->map[i]);
		i++;
	}
	free(game->world->map);
	*/
	i = 0;
	while (i < 7)
	{
		if (params->world.textures[i].img)
			mlx_destroy_image(params->mlx.ptr,
								params->world.textures[i].img);
		i++;
	}
	mlx_destroy_image(params->mlx.ptr, params->img.img);
	mlx_destroy_window(params->mlx.ptr, params->mlx.win);
	exit(status);
}

int			red_cross_press(t_data *params)
{
	exit_game(params, EXIT_SUCCESS);
	return (0);
}

// calculate ray position and direction
void set_ray_dir(int x, t_ray *ray, t_data *params) {
	t_resolution *resolution;
	t_player *player;
	double camera_x;

	resolution = &params->resolution;
	player = &params->player;
	camera_x = ((2 * x) / (double)resolution->width) - 1; // x-coordinate in camera space
	ray->dir.x = player->dir.x + player->plane.x * camera_x;
	ray->dir.y = player->dir.y + player->plane.y * camera_x;
}

// clear buffer (by setting floor and ceiling colors)
void draw_background(t_data *params) {
	t_world *world;
	t_resolution *resolution;

	world = &params->world;
	resolution = &params->resolution;
	for (int x = 0; x < resolution->width; x++)
	{
		for (int y = 0; y < resolution->height; y++)
		{
			if (y < resolution->height / 2)
				world->buffer[y][x] = world->ceiling_color;
			else
				world->buffer[y][x] = world->floor_color;
		}
	}
}

// what direction to step in x or y-direction (either +1 or -1)
void set_step_dir(t_ray *ray) {
	if (ray->dir.x < 0)
		ray->step.dir.x = -1;
	else
		ray->step.dir.x = 1;
	if (ray->dir.y < 0)
		ray->step.dir.y = -1;
	else
		ray->step.dir.y = 1;
}

// calculate initial side_dist
void set_side_dist(t_ray *ray, t_player *player) {
	if (ray->dir.x < 0)
		ray->side_dist.x = (player->pos.x - ray->box.x) * ray->delta_dist.x;
	else
		ray->side_dist.x = (ray->box.x + 1.0 - player->pos.x) * ray->delta_dist.x;
	if (ray->dir.y < 0)
		ray->side_dist.y = (player->pos.y - ray->box.y) * ray->delta_dist.y;
	else
		ray->side_dist.y = (ray->box.y + 1.0 - player->pos.y) * ray->delta_dist.y;
}

// length of ray from current position to next x or y-side
void set_delta_dist(t_ray *ray) {
	ray->delta_dist.x = fabs(1 / ray->dir.x);
	ray->delta_dist.y = fabs(1 / ray->dir.y);
}

// which box of the map we're in
void set_ray_current_box(t_ray *ray, t_player *player) {
	ray->box.x = (int)player->pos.x;
	ray->box.y = (int)player->pos.y;
}

// jump to next map square in x-direction 
void jump_to_next_x_side(t_ray *ray) {
	ray->side_dist.x += ray->delta_dist.x;
	ray->box.x += ray->step.dir.x;
	if (ray->dir.x > 0)
		ray->side = SO;
	else
		ray->side = NO;
}

// jump to next map square in y-direction 
void jump_to_next_y_side(t_ray *ray) {
	ray->side_dist.y += ray->delta_dist.y;
	ray->box.y += ray->step.dir.y;
	if (ray->dir.y > 0)
		ray->side = EA;
	else
		ray->side = WE;
}

// jump to next map square
void jump_to_next_square(t_ray *ray) {
	if (ray->side_dist.x < ray->side_dist.y)
		jump_to_next_x_side(ray);
	else
		jump_to_next_y_side(ray);
}

// Check if ray has hit a wall
int is_a_wall_hit(int box) {
	return box == 1;
}

// perform DDA: a loop that increments the ray with 1 square every time until a wall is hit
void cast_ray(t_world *world, t_ray *ray) {
	while (is_a_wall_hit(world->map[ray->box.x][ray->box.y]) == 0)
		jump_to_next_square(ray);
}

void calc_ray_params(int x, t_ray *ray, t_data *params, t_player *player) {
	set_ray_dir(x, ray, params);
	set_ray_current_box(ray, player);
	set_delta_dist(ray);
	set_step_dir(ray);
	set_side_dist(ray, player);
}

// Calculate perpendicular distance projected on camera direction (Euclidean distance will give fisheye effect!)
void calc_perp_distance(t_ray *ray, t_player *player) {
	if (ray->side % 2 == 0)
		ray->perp_wall_dist = (ray->box.x - player->pos.x + (1.0 - ray->step.dir.x) / 2) / ray->dir.x;
	else
		ray->perp_wall_dist = (ray->box.y - player->pos.y + (1.0 - ray->step.dir.y) / 2) / ray->dir.y;
}

// Calculate height of line to draw on screen
void calc_line_height(t_ray *ray, t_resolution *resolution) {
	ray->line_height = (int)(resolution->height / ray->perp_wall_dist);
}

void calc_first_px_of_stripe(t_ray *ray, t_resolution *resolution) {
	ray->draw_start = -ray->line_height / 2 + resolution->height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
}

void calc_last_px_of_stripe(t_ray *ray, t_resolution *resolution) {
	ray->draw_end = ray->line_height / 2 + resolution->height / 2;
	if (ray->draw_end > resolution->height)
		ray->draw_end = resolution->height;
}

// calculate lowest and highest pixel to fill in current stripe
void calc_both_ends_of_vertical_stripe(t_ray *ray, t_resolution *resolution) {
	calc_first_px_of_stripe(ray, resolution);
	calc_last_px_of_stripe(ray, resolution);
}

// calculate value of wall_x (where exactly the wall was hit)
//  The value wallX represents the exact value where the wall was hit, not just the integer coordinates of the wall.
//  This is required to know which x-coordinate of the texture we have to use.
//  This is calculated by first calculating the exact x or y coordinate in the world,
//  and then substracting the integer value of the wall off it. Note that even if it's called wallX,
//  it's actually an y-coordinate of the wall if side==1, but it's always the x-coordinate of the texture.
void calc_wall_x(t_ray *ray, t_player *player) {
	if (ray->side % 2 == 0)
		ray->wall_x = player->pos.y + ray->perp_wall_dist * ray->dir.y;
	else
		ray->wall_x = player->pos.x + ray->perp_wall_dist * ray->dir.x;
	ray->wall_x -= floor(ray->wall_x);
}

// calculate the x-coordinate on the texture
// TEX_SIZE is width and height in texels of the textures
void calc_texture_x(t_ray *ray) {
	ray->tex_x = (int)(ray->wall_x * (double)TEX_SIZE);
	if (ray->side % 2 == 0 && ray->dir.x > 0)
		ray->tex_x = TEX_SIZE - ray->tex_x - 1;
	if (ray->side % 2 == 1 && ray->dir.y < 0)
		ray->tex_x = TEX_SIZE - ray->tex_x - 1;
}

// set how much to increase the texture coordinate per screen pixel
void set_texture_coordinate_step(t_ray *ray) {
	ray->tex_step = 1.0 * TEX_SIZE / ray->line_height;
}

// set starting texture coordinate
void set_starting_texture_coordinate(t_ray *ray, t_resolution *resolution) {
	ray->tex_pos =
		(ray->draw_start - resolution->height / 2.0 + ray->line_height / 2.0) * ray->tex_step;
}

void draw_vertical_stripe(int x, t_ray *ray, t_world *world) {
	for (int y = ray->draw_start; y < ray->draw_end; y++)
	{
		// Cast the texture coordinate to integer, and mask with (TEX_SIZE - 1) in case of overflow
		ray->tex_y = (int)ray->tex_pos & (TEX_SIZE - 1);
		ray->tex_pos += ray->tex_step;
		int color =
			world->textures[ray->side].addr[TEX_SIZE * ray->tex_y + ray->tex_x];

		if ((color & 0x00FFFFFF) != 0) // paint pixel if it isn't black, black is the invisible color
			world->buffer[y][x] =
				color; // y-coordinate first because it works per scanline
	}
}

/**
 * this is the function that draws a whole frame every time a control key is pressed
 */
int			draw_frame(t_data *params)
{
	t_mlx		*mlx;
	t_img_data	*img;
	t_player	*player;
	t_world		*world;
	t_resolution *resolution;
	t_ray		ray;

	mlx = &params->mlx;
	img = &params->img;
	player = &params->player;
	world = &params->world;
	resolution = &params->resolution;

	draw_background(params);

	// WALL CASTING LOOP
	for (int x = 0; x < resolution->width; x++)
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
		draw_vertical_stripe(x, &ray, world);

		// SET THE ZBUFFER FOR THE SPRITE CASTING
		world->z_buffer[x] = ray.perp_wall_dist; // perpendicular distance is used
	}

	// SPRITE CASTING
	// sort sprites from far to close
	for (int i = 0; i < world->num_sprites; i++)
	{
		world->sprite_order[i] = i;
		world->sprite_distance[i] =
			((player->pos.x - world->sprites[i].pos.x) *
					(player->pos.x - world->sprites[i].pos.x) +
				(player->pos.y - world->sprites[i].pos.y) *
					(player->pos.y - world->sprites[i].pos.y)); // sqrt not taken, unneeded
	}
	sort_sprites(world->sprite_order, world->sprite_distance, world->num_sprites);
	// after sorting the sprites, do the projection and draw them
	double sprite_x, sprite_y;
	for (int i = 0; i < world->num_sprites; i++)
	{
		// translate sprite position to relative to camera
		sprite_x = world->sprites[world->sprite_order[i]].pos.x - player->pos.x;
		sprite_y = world->sprites[world->sprite_order[i]].pos.y - player->pos.y;
		// transform sprite with the inverse camera matrix
		// [ plane_x   dir_x ] -1                                       [ dir_y
		// -dir_x ] [               ]       =  1/(plane_x*dir_y-dir_x*plane_y) *   [
		// ] [ plane_y   dir_y ]                                          [
		// -plane_y  plane_x ]
		double inv_det = 1.0 /
			(player->plane.x * player->dir.y -
				player->dir.x *
					player->plane.y); // required for correct matrix multiplication
		double transform_x =
			inv_det * (player->dir.y * sprite_x - player->dir.x * sprite_y);
		double transform_y = inv_det *
			(-player->plane.y * sprite_x +
				player->plane.x *
					sprite_y); // this is actually the depth inside the screen, that what z is in 3D
		int sprite_screen_x =
			(int)(((double)resolution->width / 2) * (1 + transform_x / transform_y));
		// calculate height of the sprite on screen
		int sprite_height = abs(
			(int)(resolution->height / transform_y)); // using 'transform_y' instead of
												// the real distance prevents fisheye
		// calculate lowest and highest pixel to fill in current stripe
		int draw_start_y = -sprite_height / 2 + resolution->height / 2;
		if (draw_start_y < 0)
			draw_start_y = 0;
		int draw_end_y = sprite_height / 2 + resolution->height / 2;
		if (draw_end_y >= resolution->height)
			draw_end_y = resolution->height - 1;
		// calculate width of the sprite
		int sprite_width = abs((int)(resolution->height / transform_y));
		int draw_start_x = -sprite_width / 2 + sprite_screen_x;
		if (draw_start_x < 0)
			draw_start_x = 0;
		int draw_end_x = sprite_width / 2 + sprite_screen_x;
		if (draw_end_x >= resolution->width)
			draw_end_x = resolution->width - 1;
		// loop through every vertical stripe of the sprite on screen
		for (int stripe = draw_start_x; stripe < draw_end_x; stripe++)
		{
			int tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) *
								TEX_SIZE / sprite_width) /
				256;
			// the conditions in the if are:
			// 1) it's in front of camera plane so you don't see things behind you
			// 2) it's on the screen (left)
			// 3) it's on the screen (right)
			// 4) z_buffer, with perpendicular distance
			if (transform_y > 0 && stripe > 0 && stripe < resolution->width &&
				transform_y < world->z_buffer[stripe])
			{
				for (int y = draw_start_y; y < draw_end_y;
						y++) // for every pixel of the current stripe
				{
					int d = (y)*256 - resolution->height * 128 +
						sprite_height * 128; // 256 and 128 factors to avoid floats
					int tex_y = ((d * TEX_SIZE) / sprite_height) / 256;
					uint32_t color = world->textures[SPRITE_INDEX].addr[TEX_SIZE * tex_y + tex_x]; // get current color from the sprite texture
					if ((color & 0x00FFFFFF) != 0)
						world->buffer[y][stripe] =
							color; // paint pixel if it isn't black, black is the invisible color
				}
			}
		}
	}
	for (int x = 0; x < resolution->width; x++)
		for (int y = 0; y < resolution->height; y++)
			ft_mlx_pixel_put(img, x, y, world->buffer[y][x]);
	mlx_put_image_to_window(mlx->ptr, mlx->win, img->img, 0, 0);

	print_info(player, params);

	return (0);
}

// move forward if no wall in front of you
void move_forward(t_data *params) {
	t_player	*player;
	t_world		*world;

	player = &params->player;
	world = &params->world;
	if (world->map[(int)(player->pos.x + player->dir.x * player->speed.move_speed)]
			[(int)(player->pos.y)] % 2 == 0 /*0 enum*/)
		// collision detection: won't move if it ain't 0 (a wall)
		player->pos.x += player->dir.x * player->speed.move_speed;
	if (world->map[(int)(player->pos.x)]
			[(int)(player->pos.y + player->dir.y * player->speed.move_speed)] % 2 == 0)
		player->pos.y += player->dir.y * player->speed.move_speed;
}

// move backwards if no wall behind you
void move_backward(t_data *params) {
	t_player	*player;
	t_world		*world;

	player = &params->player;
	world = &params->world;
	if (world->map[(int)(player->pos.x - player->dir.x * player->speed.move_speed)]
			[(int)(player->pos.y)] % 2 == 0)
		player->pos.x -= player->dir.x * player->speed.move_speed;
	if (world->map[(int)(player->pos.x)]
			[(int)(player->pos.y - player->dir.y * player->speed.move_speed)] % 2 == 0)
		player->pos.y -= player->dir.y * player->speed.move_speed;
}

// move to the right if no wall is on the right
void move_right(t_data *params) {
	t_player	*player;
	t_world		*world;
	
	player = &params->player;
	world = &params->world;
	if (world->map[(int)(player->pos.x + player->plane.x * player->speed.move_speed)]
			[(int)(player->pos.y)] % 2 == 0 /*0 enum*/)
		player->pos.x += player->plane.x * player->speed.move_speed;
	if (world->map[(int)(player->pos.x)][(
				int)(player->pos.y + player->plane.y * player->speed.move_speed)] % 2 == 0)
		player->pos.y += player->plane.y * player->speed.move_speed;
}

// move to the left if no wall is on the left
void move_left(t_data *params) {
	t_player	*player;
	t_world		*world;

	player = &params->player;
	world = &params->world;
	if (world->map[(int)(player->pos.x - player->plane.x * player->speed.move_speed)]
			[(int)(player->pos.y)] % 2 == 0 /*0 enum*/)
		player->pos.x -= player->plane.x * player->speed.move_speed;
	if (world->map[(int)(player->pos.x)][(
				int)(player->pos.y - player->plane.y * player->speed.move_speed)] % 2 == 0)
		player->pos.y -= player->plane.y * player->speed.move_speed;
}

// rotate to the right
void rotate_right(t_data *params) {
	double		old_dir_x;
	double		old_plane_x;
	t_player	*player;
	t_world		*world;

	player = &params->player;
	world = &params->world;
	// both camera direction and camera plane must be rotated
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

// rotate to the left
void rotate_left(t_data *params) {
	double		old_dir_x;
	double		old_plane_x;
	t_player	*player;
	t_world		*world;

	player = &params->player;
	world = &params->world;
	// both camera direction and camera plane must be rotated
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

int			read_keys(t_data *params)
{

	if (params->keystrokes[W_KEY]) // Key W
		move_forward(params);
	if (params->keystrokes[S_KEY]) // Key S
		move_backward(params);
	if (params->keystrokes[D_KEY]) // Key D
		move_right(params);
	if (params->keystrokes[A_KEY]) // Key A
		move_left(params);
	if (params->keystrokes[RIGHT_KEY]) // Key arrow right
		rotate_right(params);
	if (params->keystrokes[LEFT_KEY]) // Key arrow left
		rotate_left(params);
	if (params->keystrokes[ESC_KEY]) // ESC key
		exit_game(params, EXIT_SUCCESS);
	draw_frame(params);
	return (0);
}

int is_control_key(int keycode) {
	return (keycode == LEFT_KEY || keycode == RIGHT_KEY ||
			keycode == W_KEY || keycode == S_KEY ||
			keycode == A_KEY || keycode == D_KEY || keycode == ESC_KEY);
}

int			key_press(int keycode, t_data *params)
{
	if (is_control_key(keycode))
		params->keystrokes[keycode] = 1;
	return (0);
}

int			key_release(int keycode, t_data *params)
{
	if (is_control_key(keycode))
		params->keystrokes[keycode] = 0;
	return (0);
}

/**
 * initiliaze all keystrokes to zero
 */
void initiliaze_keystrokes(int *keystrokes) {
	for (int i = 0; i < 127; i++)
		keystrokes[i] = 0;
}

t_img_data	load_image(char *path, t_data *params)
{
	t_img_data	texture_buffer;
	t_mlx		*mlx;

	mlx = &params->mlx;
	texture_buffer.img = mlx_xpm_file_to_image(
		mlx->ptr, path, &texture_buffer.width, &texture_buffer.height);
	if (texture_buffer.img == NULL ||
		texture_buffer.width != TEX_SIZE || texture_buffer.height != TEX_SIZE)
	{
		ft_putstr_fd("Error\n Invalid texture", 2);
		exit_game(params, EXIT_SUCCESS);
	}
	texture_buffer.addr =
		(int *)mlx_get_data_addr(texture_buffer.img,
									&texture_buffer.bits_per_pixel,
									&texture_buffer.line_length,
									&texture_buffer.endian);
	return (texture_buffer);
}

void load_textures(t_data *params) {
	t_world		*world;

	world = &params->world;
	world->textures[NO] = load_image(world->texture_paths.walls_facing_south, params);
	world->textures[SO] = load_image(world->texture_paths.walls_facing_north, params);
	world->textures[EA] = load_image(world->texture_paths.walls_facing_west, params);
	world->textures[WE] = load_image(world->texture_paths.walls_facing_east, params);
	world->textures[SPRITE_INDEX] = load_image(world->texture_paths.sprite, params);
}

void set_sprite_position(t_world *world, t_pos pos) {
	world->num_sprites += 1;
	// implement own realloc
	world->sprites = realloc(
			world->sprites, world->num_sprites * sizeof(*world->sprites));
	world->sprites[world->num_sprites - 1].pos = pos;
}

/**
 * sets number of sprites
 * and their positions
 * and allocates the sorting arrays
 */
void setup_sprites(t_data *params) {
	t_world *world;

	world = &params->world;
	world->num_sprites = 0;
	world->sprites = malloc(sizeof(*world->sprites));
	for (int x = 0; x < params->map_size.width; x++)
	{
		for (int y = 0; y < params->map_size.height; y++)
			if (world->map[x][y] == 2)
				set_sprite_position(world, (t_pos){x + 0.5, y + 0.5});
	}
	world->sprite_order = malloc(sizeof(*world->sprite_order) * world->num_sprites);
	world->sprite_distance =
		malloc(sizeof(*world->sprite_distance) * world->num_sprites);
}

void setup_buffers(t_data *params) {
	t_world *world;

	world = &params->world;
	world->buffer = malloc(sizeof(*world->buffer) * params->resolution.height);
	for (int i = 0; i < params->resolution.height; i++)
		world->buffer[i] = malloc(sizeof(*world->buffer[i]) * params->resolution.width);
	world->z_buffer = malloc(sizeof(*world->z_buffer) * params->resolution.width);
}

void set_background_colors(t_world *world) {
	world->ceiling_color = 0xD1F1F2;
	world->floor_color = 0xF7EDD9;
}

void set_texture_paths(t_world *world) {
	world->texture_paths.walls_facing_north = "../assets/textures/iron.xpm";
	world->texture_paths.walls_facing_south = "../assets/textures/grass.xpm";
	world->texture_paths.walls_facing_east = "../assets/textures/water.xpm";
	world->texture_paths.walls_facing_west = "../assets/textures/gold.xpm";
	world->texture_paths.sprite = "../assets/textures/sprite.xpm";
}

void set_player_speed(t_player *player) {
	player->speed.move_speed = 0.07;
	player->speed.rot_speed = 0.03;
}

void set_player_init_position(t_player *player, t_pos pos, t_dir dir, t_plane plane) {
	player->pos = pos;
	player->dir = dir;
	player->plane = plane;
}

/**
 * set player's position and spawning orientation in map
 * set the position of each sprite
 */
void spawn_player(t_data *params) {
	t_player *player;
	t_world	*world;
	int	cur_pos;

	player = &params->player;
	world = &params->world;
	for (int x = 0; x < params->map_size.width; x++)
		for (int y = 0; y < params->map_size.height; y++)
		{
			cur_pos = world->map[x][y];
			if (cur_pos == 'N' || cur_pos == 'S' || cur_pos == 'E' || cur_pos == 'W')
				world->map[x][y] = 0;
			if (cur_pos == 'N')
				set_player_init_position(player, (t_pos){x + 0.5, y + 0.5}, (t_dir){-1, 0}, (t_plane){0, 0.66});
			else if (cur_pos == 'S')
				set_player_init_position(player, (t_pos){x + 0.5, y + 0.5}, (t_dir){1, 0}, (t_plane){0, -0.66});
			else if (cur_pos == 'E')
				set_player_init_position(player, (t_pos){x + 0.5, y + 0.5}, (t_dir){0, 1}, (t_plane){0.66, 0});
			else if (cur_pos == 'W')
				set_player_init_position(player, (t_pos){x + 0.5, y + 0.5}, (t_dir){0, -1}, (t_plane){-0.66, 0});
		}
}

void load_game(t_data *params) {
	t_player	*player;
	t_world		*world;

	player = &params->player;
	world = &params->world;
	spawn_player(params);
	set_player_speed(player);
	set_texture_paths(world);
	set_background_colors(world);
	setup_buffers(params);
	setup_sprites(params);
	load_textures(params);
	initiliaze_keystrokes(&params->keystrokes[0]);
}

void load_mlx(t_data *params) {
	t_mlx *mlx;
	t_img_data *img;

	mlx = &params->mlx;
	img = &params->img;
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, params->resolution.width, params->resolution.height, "cub3d");
	img->img = mlx_new_image(mlx->ptr, params->resolution.width, params->resolution.height);
	img->addr = (int *)mlx_get_data_addr(
		img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
}

/**
 * temporary function before parsing the map
 */
void generate_world_map(t_data *params) {
	t_world *world;
	
	world = &params->world;
	world->map = malloc(sizeof(world->map) * params->map_size.width);

	for (int i = 0; i < params->map_size.width; i++)
	{
		world->map[i] = malloc(sizeof(*world->map) * params->map_size.height);
		for (int j = 0; j < params->map_size.height; j++) {
			if ((i == 0) ||
				(j == 0) ||
				(i == params->map_size.width - 1) ||
				(j == params->map_size.height - 1))
			{
				world->map[i][j] = 1;
			}
			else
			{
				world->map[i][j] = rand() % 6;
				if (world->map[i][j] == 4 || world->map[i][j] == 5)
					world->map[i][j] = 0;
				if (world->map[i][j] == 3)
					world->map[i][j] = 1;
			}
		}
	}

	char dirs[4] = {'N', 'S', 'E', 'W'};
	int new_dir = rand() % 4;
	int new_x_pos = rand() % (params->map_size.width - 1) + 1;
	int new_y_pos = rand() % (params->map_size.height - 1) + 1;
	int new_pos = world->map[new_x_pos][new_y_pos];
	while (new_pos > 0) {
		new_x_pos = rand() % (params->map_size.width - 1) + 1;
		new_y_pos = rand() % (params->map_size.height - 1) + 1;
		new_pos = world->map[new_x_pos][new_y_pos];
	}
	world->map[new_x_pos][new_y_pos] = dirs[new_dir];

	for (int i = 0; i < params->map_size.width; i++)
	{
		printf("\x1B[37m\"");
		for (int j = 0; j < params->map_size.height; j++)
		{
			if (world->map[i][j] > 2)
				printf("\x1B[31m%c, ", world->map[i][j]);
			else
				printf("\x1B[37m%d, ", world->map[i][j]);
		}
		printf("\b\b\"\n");
	}
}

/*
void generate_world_map(t_data *params) {
	t_world *world;
	
	world = &params->world;
	world->map = malloc(sizeof(world->map) * params->map_size.width);

	int map_buffer[24][24] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 2, 2, 1, 0, 0, 0, 0, 2, 2, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1},
		{1, 0, 1, 2, 2, 0, 2, 2, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 2, 0, 0, 1},
		{1, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 0, 2, 0, 1, 0, 0, 0, 1, 0, 0, 2, 0, 1},
		{1, 0, 0, 2, 0, 0, 2, 0, 1, 0, 0, 2, 0, 0, 2, 2, 1, 0, 0, 'S', 0, 1, 0, 1},
		{1, 0, 1, 2, 1, 0, 2, 0, 1, 0, 0, 0, 0, 2, 2, 0, 2, 0, 0, 0, 2, 0, 2, 1},
		{1, 2, 2, 0, 0, 1, 0, 2, 0, 1, 0, 2, 2, 2, 2, 0, 1, 2, 0, 0, 2, 0, 0, 1},
		{1, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 1, 2, 2, 0, 1, 1, 0, 0, 1},
		{1, 1, 1, 0, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 1, 1, 0, 0, 0, 0, 1},
		{1, 2, 2, 0, 2, 0, 2, 1, 1, 2, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 2, 0, 0, 2, 2, 0, 2, 0, 1, 0, 0, 0, 2, 0, 1, 0, 2, 2, 0, 1, 1},
		{1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
		{1, 0, 1, 2, 0, 0, 2, 2, 0, 2, 0, 2, 1, 0, 0, 1, 0, 2, 0, 0, 2, 1, 0, 1},
		{1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 1, 2, 2, 0, 0, 1, 0, 1, 0, 0, 0, 1},
		{1, 1, 0, 2, 2, 1, 2, 0, 2, 0, 0, 0, 2, 2, 0, 0, 2, 0, 0, 0, 0, 0, 1, 1},
		{1, 2, 0, 0, 2, 0, 0, 1, 1, 0, 2, 1, 0, 0, 0, 0, 1, 0, 1, 0, 2, 0, 0, 1},
		{1, 0, 0, 2, 0, 0, 0, 2, 0, 0, 1, 2, 2, 2, 2, 0, 0, 1, 0, 0, 0, 0, 2, 1},
		{1, 0, 0, 2, 0, 0, 0, 0, 2, 0, 1, 0, 0, 1, 0, 0, 2, 2, 2, 0, 1, 0, 2, 1},
		{1, 1, 0, 1, 0, 0, 1, 0, 2, 0, 0, 0, 0, 1, 0, 0, 2, 2, 0, 1, 1, 0, 1, 1},
		{1, 0, 0, 2, 1, 0, 1, 2, 0, 0, 2, 1, 0, 2, 0, 0, 2, 0, 0, 1, 2, 2, 0, 1},
		{1, 2, 0, 0, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 2, 2, 0, 0, 0, 0, 1, 1},
		{1, 0, 0, 2, 1, 0, 2, 0, 1, 0, 0, 2, 2, 0, 0, 0, 1, 0, 1, 0, 0, 2, 0, 1},
		{1, 0, 0, 2, 0, 2, 0, 2, 1, 2, 0, 1, 0, 0, 0, 0, 1, 0, 1, 2, 0, 1, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};

	for (int i = 0; i < params->map_size.width; i++)
	{
		world->map[i] = malloc(sizeof(*world->map) * params->map_size.height);
		for (int j = 0; j < params->map_size.height; j++)
			world->map[i][j] = map_buffer[i][j];
	}

	// print map in stdout
	for (int i = 0; i < params->map_size.width; i++)
	{
		printf("\x1B[37m\"");
		for (int j = 0; j < params->map_size.height; j++)
		{
			if (world->map[i][j] > 2)
				printf("\x1B[31m%c, ", world->map[i][j]);
			else
				printf("\x1B[37m%d, ", world->map[i][j]);
		}
		printf("\b\b\"\n");
	}
}
*/


void set_map_size(t_data *params) {
	params->map_size.width = 24;
	params->map_size.height = 24;
}

void set_screen_resolution(t_data *params) {
	params->resolution.width = 640;
	params->resolution.height = 480;
}

int			main()
{
	t_data		params;
	t_mlx		*mlx;
	t_img_data	*img;

	mlx = &params.mlx;
	img = &params.img;

	srand(time(NULL));
	set_screen_resolution(&params);
	set_map_size(&params);
	generate_world_map(&params);
	load_mlx(&params);
	load_game(&params);
	draw_frame(&params);
	mlx_loop_hook(mlx->ptr, read_keys, &params);
	mlx_hook(mlx->win, 2, 0, key_press, &params);
	mlx_hook(mlx->win, 3, 0, key_release, &params);
	mlx_hook(mlx->win, 17, 0, red_cross_press, &params);
	mlx_loop(mlx->ptr);
}
