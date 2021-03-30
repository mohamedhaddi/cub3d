/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 21:35:54 by mhaddi            #+#    #+#             */
/*   Updated: 2021/03/30 19:31:33 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx/mlx.h"
#include <stdlib.h>

int	worldMap[mapWidth][mapHeight] = {
	{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
	{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 4},
	{4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	{4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	{4, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 4},
	{4, 0, 4, 0, 0, 0, 0, 3, 4, 4, 4, 3, 3, 3, 3, 2, 2, 4, 0, 4, 4, 3, 3, 4},
	{4, 0, 1, 0, 0, 0, 0, 4, 0, 4, 0, 3, 0, 3, 0, 1, 2, 0, 0, 0, 4, 3, 3, 4},
	{4, 0, 1, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 0, 4},
	{4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 3, 3, 4},
	{4, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 0, 4},
	{4, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 0, 0, 4, 3, 3, 4},
	{4, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 0, 2, 3, 3, 1, 2, 4, 4, 4, 4, 3, 3, 4},
	{3, 3, 4, 1, 4, 1, 2, 2, 4, 4, 4, 0, 1, 3, 1, 2, 1, 3, 3, 4, 4, 3, 3, 4},
	{2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	{1, 4, 4, 4, 4, 2, 0, 4, 4, 4, 3, 0, 3, 3, 1, 2, 1, 3, 4, 4, 3, 3, 1, 4},
	{4, 3, 4, 4, 4, 4, 0, 4, 4, 4, 3, 0, 3, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 4},
	{4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 3, 0, 3, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 4},
	{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 2, 0, 0, 2, 0, 0, 2, 0, 0, 0, 4},
	{4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 1, 0, 1, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 4},
	{4, 0, 2, 0, 3, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 4},
	{4, 0, 0, 1, 0, 0, 0, 0, 0, 4, 2, 0, 3, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 4},
	{4, 0, 2, 0, 1, 0, 0, 0, 0, 4, 3, 0, 3, 2, 0, 0, 1, 0, 0, 2, 0, 0, 0, 4},
	{4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 3, 0, 3, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 4},
	{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3}};

/**
 * test
 */

t_texture loadImage(char *path, t_data *params)
{
	t_texture	texture_buffer;
	t_mlx 		*mlx;

	mlx = &params->mlx;

	texture_buffer.texture_img_data.img = mlx_xpm_file_to_image(mlx->ptr, path, &texture_buffer.width, &texture_buffer.height);

	if (texture_buffer.texture_img_data.img == NULL || texture_buffer.width != texSize || texture_buffer.height != texSize)
	{
		//ft_putstr_fd("Error\n Invalid texture", 2);
		printf("Error: Invalid texture\n");
		printf("texWidth: %d\n", texture_buffer.width);
		printf("texHeight: %d\n", texture_buffer.height);
		exit(0);
	}

	texture_buffer.texture_img_data.addr = (int *)mlx_get_data_addr(texture_buffer.texture_img_data.img,
												&texture_buffer.texture_img_data.bits_per_pixel,
												&texture_buffer.texture_img_data.line_length,
												&texture_buffer.texture_img_data.endian);
	return (texture_buffer);
}

int	draw_frame(t_data *params)
{
	t_mlx		*mlx;
	t_img_data	*img;
	t_player	*player;
	t_world		*world;
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
	double		deltaDistX;
	double		deltaDistY;
	int			texX;
	double		step;
	int			texY;
	int			color;
	char		*outputPosX;
	char		*outputPosY;
	char		*outputDirX;
	char		*outputDirY;
    int         texNum;
    double      wallX; 
	int			ceilingColor;
	int			floorColor;

	mlx = &params->mlx;
	img = &params->img;
	player = &params->player;
	world = &params->world;
	ceilingColor = 0xD1F1F2;
	floorColor = 0xF7EDD9;

	// clear buffer (by setting floor and ceiling colors)
	for (int x = 0; x < screenWidth; x++)
	{
		for (int y = 0; y < screenHeight; y++)
		{
			// world->buffer[y][x] = 0x00000000;
			if (y < screenHeight / 2)
				world->buffer[y][x] = ceilingColor;
			else
				world->buffer[y][x] = floorColor;
		}
	}

	// here starts the raycasting loop
	for (int x = 0; x < screenWidth; x++)
	{
		// calculate ray position and direction
		double cameraX = 2 * x / (double)screenWidth - 1; // x-coordinate in camera space
		rayDirX = player->dirX + player->planeX * cameraX;
		rayDirY = player->dirY + player->planeY * cameraX;

		// which box of the map we're in
		mapX = (int)player->posX;
		mapY = (int)player->posY;

		// length of ray from current position to next x or y-side
		deltaDistX = fabs(1 / rayDirX);
		deltaDistY = fabs(1 / rayDirY);

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
		// a loop that increments the ray with 1 square every time until a wall is hit
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

		// Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (side == 0)
			perpWallDist = (mapX - player->posX + (1.0 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - player->posY + (1.0 - stepY) / 2) / rayDirY;

		// Calculate height of line to draw on screen
		lineHeight = (int)(screenHeight / perpWallDist);

		// calculate lowest and highest pixel to fill in current stripe
		drawStart = -lineHeight / 2 + screenHeight / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + screenHeight / 2;
		if (drawEnd >= screenHeight)
			drawEnd = screenHeight - 1;

		// texturing calculations
		texNum = worldMap[mapX][mapY] - 1; // 1 subtracted from it so that texture 0 can be used!

		// calculate value of wallX (where exactly the wall was hit)
		if (side == 0)
			wallX = player->posY + perpWallDist * rayDirY;
		else
			wallX = player->posX + perpWallDist * rayDirX;
		wallX -= floor(wallX);

		// x coordinate on the texture
        // texSize and texSize are width and height in texels of the textures
		texX = (int)(wallX * (double)texSize);
		if (side == 0 && rayDirX > 0)
			texX = texSize - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = texSize - texX - 1;

		// How much to increase the texture coordinate per screen pixel
		step = 1.0 * texSize / lineHeight;

		// Starting texture coordinate
		double texPos = (drawStart - screenHeight / 2.0 + lineHeight / 2.0) * step;

		for (int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texSize - 1) in case of overflow
			texY = (int)texPos & (texSize - 1);
			texPos += step;

			color = world->textures[texNum].texture_img_data.addr[texSize * texY + texX];

			// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if (side == 1)
				color = (color >> 1) & 8355711;

			world->buffer[y][x] = color; // y-coordinate first because it works per scanline
		}
	}

	for (int x = 0; x < screenWidth; x++)
		for (int y = 0; y < screenHeight; y++)
			ft_mlx_pixel_put(img, x, y, world->buffer[y][x]);

	mlx_put_image_to_window(mlx->ptr, mlx->win, img->img, 0, 0);

    // show real-time values for cetain variables on screen
	outputPosX = (char *)malloc(20 * sizeof(char));
	outputPosY = (char *)malloc(20 * sizeof(char));
	outputDirX = (char *)malloc(20 * sizeof(char));
	outputDirY = (char *)malloc(20 * sizeof(char));
    char *outputKeystrokesF = (char *)malloc(20 * sizeof(char));
    char *outputKeystrokesB = (char *)malloc(20 * sizeof(char));
    char *outputKeystrokesR = (char *)malloc(20 * sizeof(char));
    char *outputKeystrokesL = (char *)malloc(20 * sizeof(char));

	sprintf(outputPosX, "posX: %f", player->posX);
	sprintf(outputPosY, "posY: %f", player->posY);
	sprintf(outputDirX, "dirX: %f", player->dirX);
	sprintf(outputDirY, "dirY: %f", player->dirY);
	sprintf(outputKeystrokesF, "keyF: %d", params->keystrokes[126]);
	sprintf(outputKeystrokesB, "keyB: %d", params->keystrokes[125]);
	sprintf(outputKeystrokesR, "keyR: %d", params->keystrokes[124]);
	sprintf(outputKeystrokesL, "keyL: %d", params->keystrokes[123]);

	mlx_string_put(mlx->ptr, mlx->win, 0, 0, 0x00FFFFFF, outputPosX);
	mlx_string_put(mlx->ptr, mlx->win, 0, 20, 0x00FFFFFF, outputPosY);
	mlx_string_put(mlx->ptr, mlx->win, 0, 40, 0x00FFFFFF, outputDirX);
	mlx_string_put(mlx->ptr, mlx->win, 0, 60, 0x00FFFFFF, outputDirY);
	mlx_string_put(mlx->ptr, mlx->win, 0, 80, 0x00FFFFFF, outputKeystrokesF);
	mlx_string_put(mlx->ptr, mlx->win, 0, 100, 0x00FFFFFF, outputKeystrokesB);
	mlx_string_put(mlx->ptr, mlx->win, 0, 120, 0x00FFFFFF, outputKeystrokesR);
	mlx_string_put(mlx->ptr, mlx->win, 0, 140, 0x00FFFFFF, outputKeystrokesL);

	return (0);
}

int	read_keys(t_data *params)
{
	t_player	*player;
	double		oldDirX;
	double		oldPlaneX;

	player = &params->player;

	// move forward if no wall in front of you
	if (params->keystrokes[126])
	{
		if (worldMap[(int)(player->posX + player->dirX * player->moveSpeed)][(int)(player->posY)] == 0 /*0 enum*/)
			// collision detection: won't move if it ain't 0 (a wall)
			player->posX += player->dirX * player->moveSpeed;
		if (worldMap[(int)(player->posX)] [(int)(player->posY + player->dirY * player->moveSpeed)] == 0)
			player->posY += player->dirY * player->moveSpeed;
	}

	// move backwards if no wall behind you
	if (params->keystrokes[125])
	{
		if (worldMap[(int)(player->posX - player->dirX * player->moveSpeed)][(int)(player->posY)] == 0)
			player->posX -= player->dirX * player->moveSpeed;
		if (worldMap[(int)(player->posX)][(int)(player->posY - player->dirY * player->moveSpeed)] == 0)
			player->posY -= player->dirY * player->moveSpeed;
	}

	// rotate to the right
	if (params->keystrokes[124])
	{
		// both camera direction and camera plane must be rotated
		oldDirX = player->dirX;
		player->dirX = player->dirX * cos(-player->rotSpeed) - player->dirY * sin(-player->rotSpeed);
		player->dirY = oldDirX * sin(-player->rotSpeed) + player->dirY * cos(-player->rotSpeed);

		oldPlaneX = player->planeX;
		player->planeX = player->planeX * cos(-player->rotSpeed) - player->planeY * sin(-player->rotSpeed);
		player->planeY = oldPlaneX * sin(-player->rotSpeed) + player->planeY * cos(-player->rotSpeed);
	}

	// rotate to the left
	if (params->keystrokes[123])
	{
		// both camera direction and camera plane must be rotated
		oldDirX = player->dirX;
		player->dirX = player->dirX * cos(player->rotSpeed) - player->dirY * sin(player->rotSpeed);
		player->dirY = oldDirX * sin(player->rotSpeed) + player->dirY * cos(player->rotSpeed);

		oldPlaneX = player->planeX;
		player->planeX = player->planeX * cos(player->rotSpeed) - player->planeY * sin(player->rotSpeed);
		player->planeY = oldPlaneX * sin(player->rotSpeed) + player->planeY * cos(player->rotSpeed);
	}

	draw_frame(params);

	return (0);
}

int	key_press(int keycode, t_data *params)
{
	if (keycode == 123 || keycode == 124 || keycode == 125 || keycode == 126)
	{
		params->keystrokes[keycode] = 1;
	}
	return (0);
}

int	key_release(int keycode, t_data *params)
{
	if (keycode == 123 || keycode == 124 || keycode == 125 || keycode == 126)
	{
		params->keystrokes[keycode] = 0;
	}
	return (0);
}

int	main()
{
	t_data		params;
	t_mlx		*mlx;
	t_img_data	*img;
	t_player	*player;
	t_world		*world;
    int         *keystrokes;

	mlx = &params.mlx;
	img = &params.img;
	player = &params.player;
	world = &params.world;

    // initiliaze keystrokes values with 0
    keystrokes = &params.keystrokes[0];
    for (int i = 123; i < 127; i++)
      keystrokes[i] = 0;

	player->posX = 22, player->posY = 12; // x and y start position of the player
	player->dirX = -1, player->dirY = 0;  // initial direction vector
	player->planeX = 0, player->planeY = 0.66; // the 2d raycaster version of camera plane
	player->moveSpeed = 0.07;
	player->rotSpeed = 0.03;

	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, screenWidth, screenHeight, "cub3d");

	// generate some textures
	world->textures[0] = loadImage("../assets/textures/gold.xpm", &params);
  	world->textures[1] = loadImage("../assets/textures/grass.xpm", &params);
  	world->textures[2] = loadImage("../assets/textures/water.xpm", &params);
  	world->textures[3] = loadImage("../assets/textures/iron.xpm", &params);

	img->img = mlx_new_image(mlx->ptr, screenWidth, screenHeight);
	img->addr = (int *)mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);

	// this was the game loop that draws a whole frame and reads the input every time
	draw_frame(&params);

	// mlx_key_hook(mlx->win, read_keys, &params);
	mlx_hook(mlx->win, 2, 0, key_press, &params);
	mlx_hook(mlx->win, 3, 0, key_release, &params);
	mlx_loop_hook(mlx->ptr, read_keys, &params);
	mlx_loop(mlx->ptr);
}
