/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 21:35:54 by mhaddi            #+#    #+#             */
/*   Updated: 2021/03/15 17:57:32 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx/mlx.h"

#define mapWidth 24
#define mapHeight 24
#define screen_width 640
#define screen_height 480

int	worldMap[mapWidth][mapHeight] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

int	game_loop(t_data *params)
{
	t_mlx		*mlx;
	t_img_data	*img;
	t_player	*player;
	double		rayDirX;
	double		rayDirY;
	int			mapX;
	int			mapY;
	double		sideDistX;
	double		sideDistY;
	double		perpWallDist;
	int			stepX;
	int			stepY;
	int			lineHeight;
	int			drawStart;
	int			drawEnd;
	int			color;

	mlx = &params->mlx;
	img = &params->img;
	player = &params->player;
	// here starts the raycasting loop
	for (int x = 0; x < screen_width; x++)
	{
		// calculate ray position and direction
		double cameraX =
			2 * x / (double)screen_width - 1; // x-coordinate in camera space
		rayDirX = player->dirX + player->planeX * cameraX;
		rayDirY = player->dirY + player->planeY * cameraX;
		// which box of the map we're in
		mapX = (int)player->posX;
		mapY = (int)player->posY;
		// length of ray from current position to next x or y-side
		// length of ray from one x or y-side to next x or y-side
		/// double deltaDistX = fabs(1 / rayDirX);
		// double deltaDistY = fabs(1 / rayDirY);
		// Alternative code for deltaDist in case division through zero is not
		// supported
		double deltaDistX =
			(rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : fabs(1 / rayDirX));
		double deltaDistY =
			(rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : fabs(1 / rayDirY));
		// what direction to step in x or y-direction (either +1 or -1)
		int hit = 0; // was there a wall hit?
		int side;    // was a NS or a EW wall hit?
		// calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (player->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - player->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (player->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - player->posY) * deltaDistY;
		}
		// perform DDA
		// a loop that increments the ray with 1 square every time until a wall
		// is hit
		while (hit == 0)
		{
			// jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			// Check if ray has hit a wall
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		}
		// Calculate distance projected on camera direction (Euclidean distance
		// will give fisheye effect!)
		if (side == 0)
			perpWallDist = (mapX - player->posX + (1.0 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - player->posY + (1.0 - stepY) / 2) / rayDirY;
		// Calculate height of line to draw on screen
		lineHeight = (int)(screen_height / perpWallDist);
		// calculate lowest and highest pixel to fill in current stripe
		drawStart = -lineHeight / 2 + screen_height / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + screen_height / 2;
		if (drawEnd >= screen_height)
			drawEnd = screen_height - 1;
		// choose wall color
		switch (worldMap[mapX][mapY])
		{
		case 1:
			color = 0x00FF0000;
			break ; // red
		case 2:
			color = 0x0000FF00;
			break ; // green
		case 3:
			color = 0x000000FF;
			break ; // blue
		case 4:
			color = 0x00FFFFFF;
			break ; // white
		default:
			color = 0x0000FFFF;
			break ; // yellow
		}
		// give x and y sides different brightness
		// if (side == 1) {color = color / 2;}
		// draw the pixels of the stripe as a vertical line
		// verLine(x, drawStart, drawEnd, color);
		for (int y = drawStart; y <= drawEnd; y++)
		{
			ft_mlx_pixel_put(img, x, y, color);
		}
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win, img->img, 0, 0);
	// clear
	for (int x = 0; x <= screen_width; x++)
	{
		for (int y = 0; y <= screen_height; y++)
		{
			ft_mlx_pixel_put(img, x, y, 0x00000000);
		}
	}
	return (0);
}

int	read_keys(t_data *params)
{
	t_player	*player;
	double		oldDirX;
	double		oldPlaneX;

	player = &params->player;

	// move forward if no wall in front of you
	if (params->keystroke[126])
	{
		printf("posX: %f\nposY: %f\ndirX: %f\ndirY: %f\n\n",
				player->posX,
				player->posY,
				player->dirX,
				player->dirY);
		if (worldMap[(int)(player->posX + player->dirX * player->moveSpeed)]
					[(int)(player->posY)] == 0 /*0 enum*/)
			player->posX += player->dirX * player->moveSpeed;
		if (worldMap[(int)(player->posX)]
					[(int)(player->posY + player->dirY * player->moveSpeed)] == 0)
			player->posY += player->dirY * player->moveSpeed;
	}
	// move backwards if no wall behind you
	if (params->keystroke[125])
	{
		printf("posX: %f\nposY: %f\ndirX: %f\ndirY: %f\n\n",
				player->posX,
				player->posY,
				player->dirX,
				player->dirY);
		if (worldMap[(int)(player->posX - player->dirX * player->moveSpeed)]
					[(int)(player->posY)] == 0)
			player->posX -= player->dirX * player->moveSpeed;
		if (worldMap[(int)(player->posX)]
					[(int)(player->posY - player->dirY * player->moveSpeed)] == 0)
			player->posY -= player->dirY * player->moveSpeed;
	}
	// rotate to the right
	if (params->keystroke[124])
	{
		printf("posX: %f\nposY: %f\ndirX: %f\ndirY: %f\n\n",
				player->posX,
				player->posY,
				player->dirX,
				player->dirY);
		// both camera direction and camera plane must be rotated
		oldDirX = player->dirX;
		player->dirX = player->dirX * cos(-player->rotSpeed) -
			player->dirY * sin(-player->rotSpeed);
		player->dirY = oldDirX * sin(-player->rotSpeed) +
			player->dirY * cos(-player->rotSpeed);
		oldPlaneX = player->planeX;
		player->planeX = player->planeX * cos(-player->rotSpeed) -
			player->planeY * sin(-player->rotSpeed);
		player->planeY = oldPlaneX * sin(-player->rotSpeed) +
			player->planeY * cos(-player->rotSpeed);
	}
	// rotate to the left
	if (params->keystroke[123])
	{
		printf("posX: %f\nposY: %f\ndirX: %f\ndirY: %f\n\n",
				player->posX,
				player->posY,
				player->dirX,
				player->dirY);
		// both camera direction and camera plane must be rotated
		oldDirX = player->dirX;
		player->dirX = player->dirX * cos(player->rotSpeed) -
			player->dirY * sin(player->rotSpeed);
		player->dirY = oldDirX * sin(player->rotSpeed) +
			player->dirY * cos(player->rotSpeed);
		oldPlaneX = player->planeX;
		player->planeX = player->planeX * cos(player->rotSpeed) -
			player->planeY * sin(player->rotSpeed);
		player->planeY = oldPlaneX * sin(player->rotSpeed) +
			player->planeY * cos(player->rotSpeed);
	}
	game_loop(params);
	return (0);
}

int	key_press(int keycode, t_data *params)
{
	if (keycode == 123 || keycode == 124 || keycode == 125 ||
		keycode == 126)
	{
		params->keystroke[keycode] = 1;
	}
	return (0);
}

int	key_release(int keycode, t_data *params)
{
	if (keycode == 123 || keycode == 124 || keycode == 125 ||
		keycode == 126)
	{
		params->keystroke[keycode] = 0;
	}
	return (0);
}

int	main()
{
	t_data		params;
	t_mlx		*mlx;
	t_img_data	*img;
	t_player	*player;

	mlx = &params.mlx;
	img = &params.img;
	player = &params.player;
	// memset(params.keystroke, 0, 127);
	params.keystroke[126] = 0;
	params.keystroke[125] = 0;
	params.keystroke[124] = 0;
	params.keystroke[123] = 0;
	player->posX = 22, player->posY = 12; // x and y start position of the player
	player->dirX = -1, player->dirY = 0;  // initial direction vector
	player->planeX = 0,
	player->planeY = 0.66; // the 2d raycaster version of camera plane
	player->moveSpeed = 0.1;
	player->rotSpeed = 0.02;
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, screen_width, screen_height, "cub3d");
	img->img = mlx_new_image(mlx->ptr, screen_width, screen_height);
	img->addr = mlx_get_data_addr(
		img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	// this is the game loop that draws a whole frame and reads the input every
	// time
	game_loop(&params);
	// mlx_key_hook(mlx->win, read_keys, &params);
	mlx_hook(mlx->win, 2, 0, key_press, &params);
	mlx_hook(mlx->win, 3, 0, key_release, &params);
	mlx_loop_hook(mlx->ptr, read_keys, &params);
	// mlx_do_key_autorepeaton(mlx->ptr);
	mlx_loop(mlx->ptr);
}
