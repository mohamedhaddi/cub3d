/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 21:35:54 by mhaddi            #+#    #+#             */
/*   Updated: 2021/04/08 19:36:40 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include "cub3d.h"

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
		if (params->world.textures[i].texture_img_data.img)
			mlx_destroy_image(params->mlx.ptr,
								params->world.textures[i].texture_img_data.img);
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

int			is_integer(double val)
{
	int	truncated;

	truncated = (int)val;
	return (val == truncated);
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
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		delta_dist_x;
	double		delta_dist_y;
	int			tex_x;
	double		step;
	int			tex_y;
	int			color;
	char		*output_pos_x;
	char		*output_pos_y;
	char		*output_dir_x;
	char		*output_dir_y;
	int			tex_num;
	double		wall_x;
	int			ceiling_color;
	int			floor_color;
	char		*output_keystrokes_f;
	char		*output_keystrokes_b;
	char		*output_keystrokes_r;
	char		*output_keystrokes_l;
	int			draw_start_y;
	int			draw_end_y;
	int			sprite_width;
	int			draw_start_x;
	int			draw_end_x;
	char		*output_keystrokes_d;
	char		*output_keystrokes_a;
	t_resolution *resolution;

	mlx = &params->mlx;
	img = &params->img;
	player = &params->player;
	world = &params->world;
	resolution = &params->resolution;
	ceiling_color = 0xD1F1F2;
	floor_color = 0xF7EDD9;
	// clear buffer (by setting floor and ceiling colors)
	for (int x = 0; x < resolution->width; x++)
	{
		for (int y = 0; y < resolution->height; y++)
		{
			// world->buffer[y][x] = 0x00000000;
			if (y < resolution->height / 2)
				world->buffer[y][x] = ceiling_color;
			else
				world->buffer[y][x] = floor_color;
		}
	}
	// here starts the wall raycasting loop
	for (int x = 0; x < resolution->width; x++)
	{
		// calculate ray position and direction
		double camera_x =
			2 * x / (double)resolution->width - 1; // x-coordinate in camera space
		ray_dir_x = player->dir.x + player->plane.x * camera_x;
		ray_dir_y = player->dir.y + player->plane.y * camera_x;
		// if the player's position is integer, it might intersect with the
		// corner of a wall with may cause a problem in displaying it,
		// so we make it a bit further away by 0.1 from the corner
		if (is_integer(player->pos.x))
		{
			player->pos.x -= 0.1;
		}
		if (is_integer(player->pos.y))
		{
			player->pos.y -= 0.1;
		}
		// which box of the map we're in
		map_x = (int)player->pos.x;
		map_y = (int)player->pos.y;
		// length of ray from current position to next x or y-side
		delta_dist_x = fabs(1 / ray_dir_x);
		delta_dist_y = fabs(1 / ray_dir_y);
		// what direction to step in x or y-direction (either +1 or -1)
		int hit = 0; // was there a wall hit?
		int side;    // was a NS or a EW wall hit?
		// calculate step and initial side_dist
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (player->pos.x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - player->pos.x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (player->pos.y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - player->pos.y) * delta_dist_y;
		}
		// perform DDA
		// a loop that increments the ray with 1 square every time until a wall is hit
		while (hit == 0)
		{
			// jump to next map square, OR in x-direction, OR in y-direction
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				if (ray_dir_x > 0)
					side = SO;
				else
					side = NO;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				if (ray_dir_y > 0)
					side = EA;
				else
					side = WE;
			}
			// Check if ray has hit a wall
			if (world->map[map_x][map_y] > 0)
				hit = 1;
		}
		tex_num = side;
		// Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (side % 2 == 0)
			perp_wall_dist = (map_x - player->pos.x + (1.0 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - player->pos.y + (1.0 - step_y) / 2) / ray_dir_y;
		// Calculate height of line to draw on screen
		line_height = (int)(resolution->height / perp_wall_dist);
		// calculate lowest and highest pixel to fill in current stripe
		draw_start = -line_height / 2 + resolution->height / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + resolution->height / 2;
		if (draw_end >= resolution->height)
			draw_end = resolution->height - 1;
		// texturing calculations
		/*
		tex_num =
			world->map[map_x][map_y] - 1; 	// 1 subtracted from it so that
										// texture 0 can be used!
		*/
		// calculate value of wall_x (where exactly the wall was hit)
		if (side % 2 == 0)
			wall_x = player->pos.y + perp_wall_dist * ray_dir_y;
		else
			wall_x = player->pos.x + perp_wall_dist * ray_dir_x;
		wall_x -= floor(wall_x);
		// x coordinate on the texture
		// TEX_SIZE and TEX_SIZE are width and height in texels of the textures
		tex_x = (int)(wall_x * (double)TEX_SIZE);
		if (side % 2 == 0 && ray_dir_x > 0)
			tex_x = TEX_SIZE - tex_x - 1;
		if (side % 2 == 1 && ray_dir_y < 0)
			tex_x = TEX_SIZE - tex_x - 1;
		// how much to increase the texture coordinate per screen pixel
		step = 1.0 * TEX_SIZE / line_height;
		// starting texture coordinate
		double tex_pos =
			(draw_start - resolution->height / 2.0 + line_height / 2.0) * step;
		for (int y = draw_start; y <= draw_end; y++)
		{
			// Cast the texture coordinate to integer, and mask with (TEX_SIZE - 1) in case of overflow
			tex_y = (int)tex_pos & (TEX_SIZE - 1);
			tex_pos += step;
			color =
				world->textures[tex_num].texture_img_data.addr[TEX_SIZE * tex_y + tex_x];
			// make color darker for y-sides: R, G and B byte each divided
			// through two with a "shift" and an "and"
			/*
			if (side % 2 == 1)
				color = (color >> 1) & 8355711;
			*/
			if ((color & 0x00FFFFFF) != 0)
				world->buffer[y][x] =
					color; // y-coordinate first because it works per scanline
		}
		// SET THE ZBUFFER FOR THE SPRITE CASTING
		world->z_buffer[x] = perp_wall_dist; // perpendicular distance is used
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
		draw_start_y = -sprite_height / 2 + resolution->height / 2;
		if (draw_start_y < 0)
			draw_start_y = 0;
		draw_end_y = sprite_height / 2 + resolution->height / 2;
		if (draw_end_y >= resolution->height)
			draw_end_y = resolution->height - 1;
		// calculate width of the sprite
		sprite_width = abs((int)(resolution->height / transform_y));
		draw_start_x = -sprite_width / 2 + sprite_screen_x;
		if (draw_start_x < 0)
			draw_start_x = 0;
		draw_end_x = sprite_width / 2 + sprite_screen_x;
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
					tex_y = ((d * TEX_SIZE) / sprite_height) / 256;
					uint32_t color =
						world->textures[SPRITE_INDEX]
							.texture_img_data
							.addr[TEX_SIZE * tex_y +
									tex_x]; // get current color from the sprite texture
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
	return (0);
}

int			read_keys(t_data *params)
{
	t_player	*player;
	double		old_dir_x;
	double		old_plane_x;
	t_world		*world;

	player = &params->player;
	world = &params->world;
	// move forward if no wall in front of you
	if (params->keystrokes[W_KEY]) // Key W
	{
		if (world->map[(int)(player->pos.x + player->dir.x * player->speed.move_speed)]
					[(int)(player->pos.y)] == 0 /*0 enum*/)
			// collision detection: won't move if it ain't 0 (a wall)
			player->pos.x += player->dir.x * player->speed.move_speed;
		if (world->map[(int)(player->pos.x)]
					[(int)(player->pos.y + player->dir.y * player->speed.move_speed)] == 0)
			player->pos.y += player->dir.y * player->speed.move_speed;
	}
	// move backwards if no wall behind you
	if (params->keystrokes[S_KEY]) // Key S
	{
		if (world->map[(int)(player->pos.x - player->dir.x * player->speed.move_speed)]
					[(int)(player->pos.y)] == 0)
			player->pos.x -= player->dir.x * player->speed.move_speed;
		if (world->map[(int)(player->pos.x)]
					[(int)(player->pos.y - player->dir.y * player->speed.move_speed)] == 0)
			player->pos.y -= player->dir.y * player->speed.move_speed;
	}
	// move to the right if no wall is on the right
	if (params->keystrokes[D_KEY]) // Key D
	{
		if (world->map[(int)(player->pos.x + player->plane.x * player->speed.move_speed)]
					[(int)(player->pos.y)] == 0 /*0 enum*/)
			player->pos.x += player->plane.x * player->speed.move_speed;
		if (world->map[(int)(player->pos.x)][(
				int)(player->pos.y + player->plane.y * player->speed.move_speed)] == 0)
			player->pos.y += player->plane.y * player->speed.move_speed;
	}
	// move to the left if no wall is on the left
	if (params->keystrokes[A_KEY]) // Key A
	{
		if (world->map[(int)(player->pos.x - player->plane.x * player->speed.move_speed)]
					[(int)(player->pos.y)] == 0 /*0 enum*/)
			player->pos.x -= player->plane.x * player->speed.move_speed;
		if (world->map[(int)(player->pos.x)][(
				int)(player->pos.y - player->plane.y * player->speed.move_speed)] == 0)
			player->pos.y -= player->plane.y * player->speed.move_speed;
	}
	// rotate to the right
	if (params->keystrokes[RIGHT_KEY]) // Key arrow right
	{
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
	if (params->keystrokes[LEFT_KEY]) // Key arrow left
	{
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
	// exit game
	if (params->keystrokes[ESC_KEY]) // ESC key
	{
		exit_game(params, EXIT_SUCCESS);
	}
	draw_frame(params);
	return (0);
}

int is_control_key(int keycode) {
	return (keycode == LEFT_KEY || keycode == RIGHT_KEY || keycode == W_KEY || keycode == S_KEY ||
			keycode == A_KEY || keycode == D_KEY || keycode == ESC_KEY);
}

int			key_press(int keycode, t_data *params)
{
	if (is_control_key(keycode))
	{
		params->keystrokes[keycode] = 1;
	}
	return (0);
}

int			key_release(int keycode, t_data *params)
{
	if (is_control_key(keycode))
	{
		params->keystrokes[keycode] = 0;
	}
	return (0);
}

/**
 * initiliaze all keystrokes to zero
 */
void initiliaze_keystrokes(int *keystrokes) {
	for (int i = 0; i < 127; i++)
		keystrokes[i] = 0;
}

t_texture	load_image(char *path, t_data *params)
{
	t_texture	texture_buffer;
	t_mlx		*mlx;

	mlx = &params->mlx;
	texture_buffer.texture_img_data.img = mlx_xpm_file_to_image(
		mlx->ptr, path, &texture_buffer.width, &texture_buffer.height);
	if (texture_buffer.texture_img_data.img == NULL ||
		texture_buffer.width != TEX_SIZE || texture_buffer.height != TEX_SIZE)
	{
		ft_putstr_fd("Error\n Invalid texture", 2);
		exit_game(params, EXIT_SUCCESS);
	}
	texture_buffer.texture_img_data.addr =
		(int *)mlx_get_data_addr(texture_buffer.texture_img_data.img,
									&texture_buffer.texture_img_data.bits_per_pixel,
									&texture_buffer.texture_img_data.line_length,
									&texture_buffer.texture_img_data.endian);
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
		for (int y = 0; y < params->map_size.height; y++)
			if (world->map[x][y] == 2)
				set_sprite_position(world, (t_pos){x - 0.5, y - 0.5});
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

void set_player_position(t_player *player, t_pos pos, t_dir dir, t_plane plane) {
	player->pos = pos;
	player->dir = dir;
	player->plane = plane;
}

/**
 * set player's position and spawning orientation in map
 * set the position of each sprite
 */
void set_player_pos_and_dir(t_data *params) {
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
				set_player_position(player, (t_pos){x + 0.5, y + 0.5}, (t_dir){-1, 0}, (t_plane){0, 0.66});
			else if (cur_pos == 'S')
				set_player_position(player, (t_pos){x + 0.5, y + 0.5}, (t_dir){1, 0}, (t_plane){0, -0.66});
			else if (cur_pos == 'E')
				set_player_position(player, (t_pos){x + 0.5, y + 0.5}, (t_dir){0, 1}, (t_plane){0.66, 0});
			else if (cur_pos == 'W')
				set_player_position(player, (t_pos){x + 0.5, y + 0.5}, (t_dir){0, -1}, (t_plane){-0.66, 0});
		}
}

void load_game(t_data *params) {
	t_player	*player;
	t_world		*world;

	player = &params->player;
	world = &params->world;
	set_player_pos_and_dir(params);
	set_player_speed(player);
	set_texture_paths(world);
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

	// generate random map, while making sure it's surrounded by walls
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
				world->map[i][j] = rand() % 5;
				if (world->map[i][j] == 3 || world->map[i][j] == 4)
					world->map[i][j] = 0;
			}
		}
	}

	// spawn player randomly
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
