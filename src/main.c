/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 21:35:54 by mhaddi            #+#    #+#             */
/*   Updated: 2021/04/06 17:47:51 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			world_map[map_width][map_height] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 2, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 0, 0, 2, 2, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1},
	{1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1},
	{1, 1, 0, 2, 0, 0, 2, 0, 1, 1, 0, 1, 0, 1, 2, 1, 1, 1, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 0, 0, 0, 0, 2, 0, 1, 1, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1, 1, 0, 1, 0, 1, 0, 1},
	{1, 1, 0, 2, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1},
	{1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1},
	{1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1},
	{1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 2, 0, 0, 0, 0, 1},
	{1, 0, 2, 0, 0, 0, 0, 2, 1, 1, 0, 0, 0, 2, 2, 0, 1, 1, 0, 0, 0, 2, 0, 1},
	{1, 0, 0, 0, 2, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1},
	{1, 0, 0, 0, 2, 0, 0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1},
	{1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 2, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
	{1, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
	{1, 1, 2, 0, 0, 0, 0, 1, 1, 1, 0, 'E', 2, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

/**
 * test
 */

void		exit_game(t_data *params, int status)
{
	int	i;

	/*
	i = 0;
	while (game->world_map[i])
	{
		free(game->world_map[i]);
		i++;
	}
	free(game->world_map);
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

t_texture	load_image(char *path, t_data *params)
{
	t_texture	texture_buffer;
	t_mlx		*mlx;

	mlx = &params->mlx;
	texture_buffer.texture_img_data.img = mlx_xpm_file_to_image(
		mlx->ptr, path, &texture_buffer.width, &texture_buffer.height);
	if (texture_buffer.texture_img_data.img == NULL ||
		texture_buffer.width != tex_size || texture_buffer.height != tex_size)
	{
		// ft_putstr_fd("Error\n Invalid texture", 2);
		printf("Error: Invalid texture\n");
		printf("tex_width: %d\n", texture_buffer.width);
		printf("tex_height: %d\n", texture_buffer.height);
		exit(0);
	}
	texture_buffer.texture_img_data.addr =
		(int *)mlx_get_data_addr(texture_buffer.texture_img_data.img,
									&texture_buffer.texture_img_data.bits_per_pixel,
									&texture_buffer.texture_img_data.line_length,
									&texture_buffer.texture_img_data.endian);
	return (texture_buffer);
}

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

	mlx = &params->mlx;
	img = &params->img;
	player = &params->player;
	world = &params->world;
	ceiling_color = 0xD1F1F2;
	floor_color = 0xF7EDD9;
	// clear buffer (by setting floor and ceiling colors)
	for (int x = 0; x < screen_width; x++)
	{
		for (int y = 0; y < screen_height; y++)
		{
			// world->buffer[y][x] = 0x00000000;
			if (y < screen_height / 2)
				world->buffer[y][x] = ceiling_color;
			else
				world->buffer[y][x] = floor_color;
		}
	}
	// here starts the wall raycasting loop
	for (int x = 0; x < screen_width; x++)
	{
		// calculate ray position and direction
		double camera_x =
			2 * x / (double)screen_width - 1; // x-coordinate in camera space
		ray_dir_x = player->dir_x + player->plane_x * camera_x;
		ray_dir_y = player->dir_y + player->plane_y * camera_x;
		// if the player's position is integer, it might intersect with the
		// corner of a wall with may cause a problem in displaying it,
		// so we make it a bit further away by 0.1 from the corner
		if (is_integer(player->pos_x))
		{
			player->pos_x -= 0.1;
		}
		if (is_integer(player->pos_y))
		{
			player->pos_y -= 0.1;
		}
		// which box of the map we're in
		map_x = (int)player->pos_x;
		map_y = (int)player->pos_y;
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
			side_dist_x = (player->pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - player->pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (player->pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - player->pos_y) * delta_dist_y;
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
			if (world_map[map_x][map_y] > 0)
				hit = 1;
		}
		tex_num = side;
		// Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (side % 2 == 0)
			perp_wall_dist = (map_x - player->pos_x + (1.0 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - player->pos_y + (1.0 - step_y) / 2) / ray_dir_y;
		// Calculate height of line to draw on screen
		line_height = (int)(screen_height / perp_wall_dist);
		// calculate lowest and highest pixel to fill in current stripe
		draw_start = -line_height / 2 + screen_height / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + screen_height / 2;
		if (draw_end >= screen_height)
			draw_end = screen_height - 1;
		// texturing calculations
		/*
		tex_num =
			world_map[map_x][map_y] - 1; 	// 1 subtracted from it so that
										// texture 0 can be used!
		*/
		// calculate value of wall_x (where exactly the wall was hit)
		if (side % 2 == 0)
			wall_x = player->pos_y + perp_wall_dist * ray_dir_y;
		else
			wall_x = player->pos_x + perp_wall_dist * ray_dir_x;
		wall_x -= floor(wall_x);
		// x coordinate on the texture
		// tex_size and tex_size are width and height in texels of the textures
		tex_x = (int)(wall_x * (double)tex_size);
		if (side % 2 == 0 && ray_dir_x > 0)
			tex_x = tex_size - tex_x - 1;
		if (side % 2 == 1 && ray_dir_y < 0)
			tex_x = tex_size - tex_x - 1;
		// how much to increase the texture coordinate per screen pixel
		step = 1.0 * tex_size / line_height;
		// starting texture coordinate
		double tex_pos =
			(draw_start - screen_height / 2.0 + line_height / 2.0) * step;
		for (int y = draw_start; y <= draw_end; y++)
		{
			// Cast the texture coordinate to integer, and mask with (tex_size - 1) in case of overflow
			tex_y = (int)tex_pos & (tex_size - 1);
			tex_pos += step;
			color =
				world->textures[tex_num].texture_img_data.addr[tex_size * tex_y + tex_x];
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
			((player->pos_x - world->sprites[i].x) *
					(player->pos_x - world->sprites[i].x) +
				(player->pos_y - world->sprites[i].y) *
					(player->pos_y - world->sprites[i].y)); // sqrt not taken, unneeded
	}
	sort_sprites(world->sprite_order, world->sprite_distance, world->num_sprites);
	// after sorting the sprites, do the projection and draw them
	double sprite_x, sprite_y;
	for (int i = 0; i < world->num_sprites; i++)
	{
		// translate sprite position to relative to camera
		sprite_x = world->sprites[world->sprite_order[i]].x - player->pos_x;
		sprite_y = world->sprites[world->sprite_order[i]].y - player->pos_y;
		// transform sprite with the inverse camera matrix
		// [ plane_x   dir_x ] -1                                       [ dir_y
		// -dir_x ] [               ]       =  1/(plane_x*dir_y-dir_x*plane_y) *   [
		// ] [ plane_y   dir_y ]                                          [
		// -plane_y  plane_x ]
		double inv_det = 1.0 /
			(player->plane_x * player->dir_y -
				player->dir_x *
					player->plane_y); // required for correct matrix multiplication
		double transform_x =
			inv_det * (player->dir_y * sprite_x - player->dir_x * sprite_y);
		double transform_y = inv_det *
			(-player->plane_y * sprite_x +
				player->plane_x *
					sprite_y); // this is actually the depth inside the screen, that what z is in 3D
		int sprite_screen_x =
			(int)(((double)screen_width / 2) * (1 + transform_x / transform_y));
		// calculate height of the sprite on screen
		int sprite_height = abs(
			(int)(screen_height / transform_y)); // using 'transform_y' instead of
												// the real distance prevents fisheye
		// calculate lowest and highest pixel to fill in current stripe
		draw_start_y = -sprite_height / 2 + screen_height / 2;
		if (draw_start_y < 0)
			draw_start_y = 0;
		draw_end_y = sprite_height / 2 + screen_height / 2;
		if (draw_end_y >= screen_height)
			draw_end_y = screen_height - 1;
		// calculate width of the sprite
		sprite_width = abs((int)(screen_height / transform_y));
		draw_start_x = -sprite_width / 2 + sprite_screen_x;
		if (draw_start_x < 0)
			draw_start_x = 0;
		draw_end_x = sprite_width / 2 + sprite_screen_x;
		if (draw_end_x >= screen_width)
			draw_end_x = screen_width - 1;
		// loop through every vertical stripe of the sprite on screen
		for (int stripe = draw_start_x; stripe < draw_end_x; stripe++)
		{
			int tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) *
								tex_size / sprite_width) /
				256;
			// the conditions in the if are:
			// 1) it's in front of camera plane so you don't see things behind you
			// 2) it's on the screen (left)
			// 3) it's on the screen (right)
			// 4) z_buffer, with perpendicular distance
			if (transform_y > 0 && stripe > 0 && stripe < screen_width &&
				transform_y < world->z_buffer[stripe])
			{
				for (int y = draw_start_y; y < draw_end_y;
						y++) // for every pixel of the current stripe
				{
					int d = (y)*256 - screen_height * 128 +
						sprite_height * 128; // 256 and 128 factors to avoid floats
					tex_y = ((d * tex_size) / sprite_height) / 256;
					uint32_t color =
						world->textures[4]
							.texture_img_data
							.addr[tex_size * tex_y +
									tex_x]; // get current color from the sprite texture
					if ((color & 0x00FFFFFF) != 0)
						world->buffer[y][stripe] =
							color; // paint pixel if it isn't black, black is the invisible color
				}
			}
		}
	}
	for (int x = 0; x < screen_width; x++)
		for (int y = 0; y < screen_height; y++)
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
	sprintf(output_pos_x, "pos_x: %f", player->pos_x);
	sprintf(output_pos_y, "pos_y: %f", player->pos_y);
	sprintf(output_dir_x, "dir_x: %f", player->dir_x);
	sprintf(output_dir_y, "dir_y: %f", player->dir_y);
	sprintf(output_keystrokes_f, "key_f(w): %d", params->keystrokes[13]);
	sprintf(output_keystrokes_b, "key_b(s): %d", params->keystrokes[1]);
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

	player = &params->player;
	// move forward if no wall in front of you
	if (params->keystrokes[13]) // Key W
	{
		if (world_map[(int)(player->pos_x + player->dir_x * player->move_speed)]
					[(int)(player->pos_y)] == 0 /*0 enum*/)
			// collision detection: won't move if it ain't 0 (a wall)
			player->pos_x += player->dir_x * player->move_speed;
		if (world_map[(int)(player->pos_x)]
					[(int)(player->pos_y + player->dir_y * player->move_speed)] == 0)
			player->pos_y += player->dir_y * player->move_speed;
	}
	// move backwards if no wall behind you
	if (params->keystrokes[1]) // Key S
	{
		if (world_map[(int)(player->pos_x - player->dir_x * player->move_speed)]
					[(int)(player->pos_y)] == 0)
			player->pos_x -= player->dir_x * player->move_speed;
		if (world_map[(int)(player->pos_x)]
					[(int)(player->pos_y - player->dir_y * player->move_speed)] == 0)
			player->pos_y -= player->dir_y * player->move_speed;
	}
	// move to the right if no wall is on the right
	if (params->keystrokes[2]) // Key D
	{
		if (world_map[(int)(player->pos_x + player->plane_x * player->move_speed)]
					[(int)(player->pos_y)] == 0 /*0 enum*/)
			player->pos_x += player->plane_x * player->move_speed;
		if (world_map[(int)(player->pos_x)][(
				int)(player->pos_y + player->plane_y * player->move_speed)] == 0)
			player->pos_y += player->plane_y * player->move_speed;
	}
	// move to the left if no wall is on the left
	if (params->keystrokes[0]) // Key A
	{
		if (world_map[(int)(player->pos_x - player->plane_x * player->move_speed)]
					[(int)(player->pos_y)] == 0 /*0 enum*/)
			player->pos_x -= player->plane_x * player->move_speed;
		if (world_map[(int)(player->pos_x)][(
				int)(player->pos_y - player->plane_y * player->move_speed)] == 0)
			player->pos_y -= player->plane_y * player->move_speed;
	}
	// rotate to the right
	if (params->keystrokes[124]) // Key arrow right
	{
		// both camera direction and camera plane must be rotated
		old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(-player->rot_speed) -
			player->dir_y * sin(-player->rot_speed);
		player->dir_y = old_dir_x * sin(-player->rot_speed) +
			player->dir_y * cos(-player->rot_speed);
		old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cos(-player->rot_speed) -
			player->plane_y * sin(-player->rot_speed);
		player->plane_y = old_plane_x * sin(-player->rot_speed) +
			player->plane_y * cos(-player->rot_speed);
	}
	// rotate to the left
	if (params->keystrokes[123]) // Key arrow left
	{
		// both camera direction and camera plane must be rotated
		old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(player->rot_speed) -
			player->dir_y * sin(player->rot_speed);
		player->dir_y = old_dir_x * sin(player->rot_speed) +
			player->dir_y * cos(player->rot_speed);
		old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cos(player->rot_speed) -
			player->plane_y * sin(player->rot_speed);
		player->plane_y = old_plane_x * sin(player->rot_speed) +
			player->plane_y * cos(player->rot_speed);
	}
	// exit game
	if (params->keystrokes[53]) // ESC key
	{
		exit_game(params, EXIT_SUCCESS);
	}
	draw_frame(params);
	return (0);
}

int			key_press(int keycode, t_data *params)
{
	if (keycode == 123 || keycode == 124 || keycode == 13 || keycode == 1 ||
		keycode == 0 || keycode == 2 || keycode == 53)
	{
		params->keystrokes[keycode] = 1;
	}
	return (0);
}

int			key_release(int keycode, t_data *params)
{
	if (keycode == 123 || keycode == 124 || keycode == 13 || keycode == 1 ||
		keycode == 0 || keycode == 2 || keycode == 53)
	{
		params->keystrokes[keycode] = 0;
	}
	return (0);
}

int			main()
{
	t_data		params;
	t_mlx		*mlx;
	t_img_data	*img;
	t_player	*player;
	t_world		*world;
	int			*keystrokes;
	int			cur_pos;
	char		*walls_facing_north;
	char		*walls_facing_south;
	char		*walls_facing_east;
	char		*walls_facing_west;

	mlx = &params.mlx;
	img = &params.img;
	player = &params.player;
	world = &params.world;
	// initiliaze keystrokes values with 0
	keystrokes = &params.keystrokes[0];
	for (int i = 0; i < 127; i++)
		keystrokes[i] = 0;
	// get player's position and spawning orientation from map
	// and define the position of each sprite
	world->num_sprites = 0;
	world->sprites = malloc(sizeof(*world->sprites) * world->num_sprites);
	for (int i = 0; i < map_width; i++)
		for (int j = 0; j < map_height; j++)
		{
			cur_pos = world_map[i][j];
			if (cur_pos == 'N')
			{
				player->pos_x = i - 0.5;
				player->pos_y = j - 0.5;
				player->dir_x = -1;
				player->dir_y = 0;
				player->plane_x = 0, player->plane_y = 0.66;
			}
			else if (cur_pos == 'S')
			{
				player->pos_x = i - 0.5;
				player->pos_y = j - 0.5;
				player->dir_x = 1;
				player->dir_y = 0;
				player->plane_x = 0, player->plane_y = -0.66;
			}
			else if (cur_pos == 'E')
			{
				player->pos_x = i - 0.5;
				player->pos_y = j - 0.5;
				player->dir_x = 0;
				player->dir_y = 1;
				player->plane_x = 0.66, player->plane_y = 0;
			}
			else if (cur_pos == 'W')
			{
				player->pos_x = i - 0.5;
				player->pos_y = j - 0.5;
				player->dir_x = 0;
				player->dir_y = -1;
				player->plane_x = -0.66, player->plane_y = 0;
			}
			else if (cur_pos == 2)
			{
				world->num_sprites += 1;
				world->sprites = realloc(
					world->sprites, world->num_sprites * sizeof(*world->sprites));
				world->sprites[world->num_sprites - 1].x = i - 0.5;
				world->sprites[world->num_sprites - 1].y = j - 0.5;
			}
		}
	world->sprite_order = malloc(sizeof(*world->sprite_order) * world->num_sprites);
	world->sprite_distance =
		malloc(sizeof(*world->sprite_distance) * world->num_sprites);
	/*
	player->pos_x = 22, player->pos_y = 12; // x and y start position of the
	player player->dir_x = -1, player->dir_y = 0;  // initial direction vector player->plane_x
	= 0, player->plane_y = 0.66; // the 2d raycaster version of camera plane
	*/
	player->move_speed = 0.07;
	player->rot_speed = 0.03;
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, screen_width, screen_height, "cub3d");
	// generate some textures
	walls_facing_north = "../assets/textures/iron.xpm";
	walls_facing_south = "../assets/textures/grass.xpm";
	walls_facing_east = "../assets/textures/water.xpm";
	walls_facing_west = "../assets/textures/gold.xpm";
	world->textures[NO] = load_image(walls_facing_south, &params);
	world->textures[SO] = load_image(walls_facing_north, &params);
	world->textures[EA] = load_image(walls_facing_west, &params);
	world->textures[WE] = load_image(walls_facing_east, &params);
	world->textures[4] = load_image("../assets/textures/sprite.xpm", &params);
	/*
	world->textures[5] = load_image("../assets/textures/sprite-2.xpm", &params);
	world->textures[6] = load_image("../assets/textures/sprite-3.xpm", &params);
	*/
	img->img = mlx_new_image(mlx->ptr, screen_width, screen_height);
	img->addr = (int *)mlx_get_data_addr(
		img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	// this was the game loop that draws a whole frame and reads the input every time
	draw_frame(&params);
	// mlx_key_hook(mlx->win, read_keys, &params);
	mlx_hook(mlx->win, 2, 0, key_press, &params);
	mlx_hook(mlx->win, 3, 0, key_release, &params);
	mlx_hook(mlx->win, 17, 0, red_cross_press, &params);
	mlx_loop_hook(mlx->ptr, read_keys, &params);
	mlx_loop(mlx->ptr);
}
