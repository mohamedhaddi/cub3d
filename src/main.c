/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 21:35:54 by mhaddi            #+#    #+#             */
/*   Updated: 2021/04/03 16:52:55 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx/mlx.h"
#include <stdlib.h>

enum directions {NO, EA, SO, WE};

int worldMap[mapWidth][mapHeight] =
{
	{4,4,4,4,4,4,4,4,4,4,4,4,4,2,4,4,2,4,2,4,4,4,2,4},
	{4,0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,0,0,4},
	{4,0,3,3,0,0,0,0,0,4,4,4,0,0,0,0,0,0,0,0,0,0,0,2},
	{4,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{4,0,3,3,0,0,0,0,0,4,4,4,0,0,0,0,0,0,0,0,0,0,0,4},
	{4,0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,2,2,2,0,2,4,2},
	{4,4,4,4,0,4,4,4,4,4,4,4,4,4,4,4,4,2,0,0,0,0,0,2},
	{3,3,3,3,0,3,3,3,3,0,4,0,4,0,4,0,4,4,0,4,0,2,0,2},
	{3,3,0,0,0,0,0,0,3,4,0,4,0,4,0,4,4,2,0,0,0,0,0,2},
	{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,2,0,0,0,0,0,4},
	{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,2,0,2,0,2,0,2},
	{3,3,0,0,0,0,0,0,3,4,0,4,0,4,0,4,4,2,4,2,0,2,2,2},
	{3,3,3,3,0,3,3,3,3,4,4,4,0,2,4,4,4,3,3,3,0,3,3,3},
	{2,2,2,2,0,2,2,2,2,4,2,4,0,0,2,0,2,3,0,0,0,0,0,3},
	{2,2,0,0,0,0,0,2,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
	{2,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
	{1,0,0,0,0,0,0,0,1,4,4,4,4,4,2,0,2,3,3,0,0,0,3,3},
	{2,0,0,0,0,0,0,0,2,2,2,1,2,2,2,2,2,0,0,1,0,1,0,1},
	{2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,1,0,1,0,0,0,1,1},
	{2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,1,0,1,0,1,0,1,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,1,0,1,0,1,0,1,0,1},
	{2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,1,0,1,0,0,0,1,1},
	{2,2,2,2,1,2,2,2,2,2,2,1,2,2,2,1,1,1,1,1,1,1,1,1}
};

// define the positions and texture of each sprite
t_sprite sprites[numSprites] =
{
	//green light in front of playerstart
	{20.5, 11.5, 6}, 

	//green lights in every room
	{18.5,4.5, 6},
	{10.0,4.5, 6},
	{10.0,12.5,6},
	{3.5, 6.5, 6},
	{3.5, 20.5,6},
	{3.5, 14.5,6},
	{14.5,20.5,6},

	//row of pillars in front of wall: fisheye test
	{18.5, 10.5, 5},
	{18.5, 11.5, 5},
	{18.5, 12.5, 5},

	//some barrels around the map
	{21.5, 1.5, 4},
	{15.5, 1.5, 4},
	{16.0, 1.8, 4},
	{16.2, 1.2, 4},
	{3.5,  2.5, 4},
	{9.5, 15.5, 4},
	{10.0, 15.1,4},
	{10.5, 15.8,4},
};

/**
 * test
 */

void			exit_game(t_data *params, int status)
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
			mlx_destroy_image(params->mlx.ptr, params->world.textures[i].texture_img_data.img);
		i++;
	}
	mlx_destroy_image(params->mlx.ptr, params->img.img);
	mlx_destroy_window(params->mlx.ptr, params->mlx.win);
	exit(status);
}

int isInteger(double val)
{
    int truncated = (int)val;
    return (val == truncated);
}

t_texture	loadImage(char *path, t_data *params)
{
	t_texture	texture_buffer;
	t_mlx		*mlx;

	mlx = &params->mlx;

	texture_buffer.texture_img_data.img = mlx_xpm_file_to_image(
		mlx->ptr, path, &texture_buffer.width, &texture_buffer.height);

	if (texture_buffer.texture_img_data.img == NULL ||
		texture_buffer.width != texSize || texture_buffer.height != texSize)
	{
		// ft_putstr_fd("Error\n Invalid texture", 2);
		printf("Error: Invalid texture\n");
		printf("texWidth: %d\n", texture_buffer.width);
		printf("texHeight: %d\n", texture_buffer.height);
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
	int			texNum;
	double		wallX;
	int			ceilingColor;
	int			floorColor;
	char		*outputKeystrokesF;
	char		*outputKeystrokesB;
	char		*outputKeystrokesR;
	char		*outputKeystrokesL;

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

	// here starts the wall raycasting loop
	for (int x = 0; x < screenWidth; x++)
	{
		// calculate ray position and direction
		double cameraX =
			2 * x / (double)screenWidth - 1; // x-coordinate in camera space
		rayDirX = player->dirX + player->planeX * cameraX;
		rayDirY = player->dirY + player->planeY * cameraX;

		// if the player's position is integer, it might intersect with the
		// corner of a wall with may cause a problem in displaying it,
		// so we make it a bit further away by 0.1 from the corner
		if (isInteger(player->posX)) {
			player->posX -= 0.1;
		}
		if (isInteger(player->posY)) {
			player->posY -= 0.1;
		}

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
				if (rayDirX > 0)
					side = SO;
				else
					side = NO;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				if (rayDirY > 0)
					side = EA;
				else
					side = WE;
			}

			// Check if ray has hit a wall
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		}

		texNum = side;

		// Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (side % 2 == 0)
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
		/*
		texNum =
			worldMap[mapX][mapY] - 1; 	// 1 subtracted from it so that
										// texture 0 can be used!
		*/

		// calculate value of wallX (where exactly the wall was hit)
		if (side % 2 == 0)
			wallX = player->posY + perpWallDist * rayDirY;
		else
			wallX = player->posX + perpWallDist * rayDirX;
		wallX -= floor(wallX);

		// x coordinate on the texture
		// texSize and texSize are width and height in texels of the textures
		texX = (int)(wallX * (double)texSize);
		if (side % 2 == 0 && rayDirX > 0)
			texX = texSize - texX - 1;
		if (side % 2 == 1 && rayDirY < 0)
			texX = texSize - texX - 1;

		// How much to increase the texture coordinate per screen pixel
		step = 1.0 * texSize / lineHeight;

		// Starting texture coordinate
		double texPos =
			(drawStart - screenHeight / 2.0 + lineHeight / 2.0) * step;

		for (int y = drawStart; y <= drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texSize - 1) in case of overflow
			texY = (int)texPos & (texSize - 1);

			texPos += step;

			color =
				world->textures[texNum].texture_img_data.addr[texSize * texY + texX];

			// make color darker for y-sides: R, G and B byte each divided
			// through two with a "shift" and an "and"
			/*
			if (side % 2 == 1)
				color = (color >> 1) & 8355711;
			*/

			if((color & 0x00FFFFFF) != 0)
				world->buffer[y][x] =
					color; // y-coordinate first because it works per scanline
		}

		//SET THE ZBUFFER FOR THE SPRITE CASTING
		world->ZBuffer[x] = perpWallDist; //perpendicular distance is used
	}

	//SPRITE CASTING

	//sort sprites from far to close
	for(int i = 0; i < numSprites; i++)
	{
		world->spriteOrder[i] = i;
		world->spriteDistance[i] = ((player->posX - sprites[i].x) * (player->posX - sprites[i].x) + 
				(player->posY - sprites[i].y) * (player->posY - sprites[i].y)); //sqrt not taken, unneeded
	}
	sort_sprites(world->spriteOrder, world->spriteDistance, numSprites);

	//after sorting the sprites, do the projection and draw them
	double spriteX, spriteY;
	for (int i = 0; i < numSprites; i++)
	{
		//translate sprite position to relative to camera
		spriteX = sprites[world->spriteOrder[i]].x - player->posX;
		spriteY = sprites[world->spriteOrder[i]].y - player->posY;

		//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]
		double invDet = 1.0 / (player->planeX * player->dirY - player->dirX * player->planeY); //required for correct matrix multiplication
		double transformX = invDet * (player->dirY * spriteX - player->dirX * spriteY);
		double transformY =
			invDet *
			(-player->planeY * spriteX + player->planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D
		int spriteScreenX = (int)(((double)screenWidth / 2) * (1 + transformX / transformY));

		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(screenHeight / transformY)); //using 'transformY' instead of the real distance prevents fisheye

		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + screenHeight / 2;
		if(drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + screenHeight / 2;
		if(drawEndY >= screenHeight) drawEndY = screenHeight - 1;

		//calculate width of the sprite
		int spriteWidth = abs((int)(screenHeight / transformY));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= screenWidth) drawEndX = screenWidth - 1;

		//loop through every vertical stripe of the sprite on screen
		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texSize / spriteWidth) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if(transformY > 0 && stripe > 0 && stripe < screenWidth && transformY < world->ZBuffer[stripe])
			{
				for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
				{
					int d = (y) * 256 - screenHeight * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
					int texY = ((d * texSize) / spriteHeight) / 256;
					uint32_t color = world->textures[sprites[world->spriteOrder[i]].texture]
						.texture_img_data.addr[texSize * texY + texX]; //get current color from the texture
					if((color & 0x00FFFFFF) != 0)
						world->buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
				}
			}
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
	outputKeystrokesF = (char *)malloc(20 * sizeof(char));
	outputKeystrokesB = (char *)malloc(20 * sizeof(char));
	outputKeystrokesR = (char *)malloc(20 * sizeof(char));
	outputKeystrokesL = (char *)malloc(20 * sizeof(char));
	char *outputKeystrokesD = (char *)malloc(20 * sizeof(char));
	char *outputKeystrokesA = (char *)malloc(20 * sizeof(char));
	sprintf(outputPosX, "posX: %f", player->posX);
	sprintf(outputPosY, "posY: %f", player->posY);
	sprintf(outputDirX, "dirX: %f", player->dirX);
	sprintf(outputDirY, "dirY: %f", player->dirY);
	sprintf(outputKeystrokesF, "keyF(W): %d", params->keystrokes[13]);
	sprintf(outputKeystrokesB, "keyB(S): %d", params->keystrokes[1]);
	sprintf(outputKeystrokesR, "keyR: %d", params->keystrokes[124]);
	sprintf(outputKeystrokesL, "keyL: %d", params->keystrokes[123]);
	sprintf(outputKeystrokesD, "keyD: %d", params->keystrokes[2]);
	sprintf(outputKeystrokesA, "keyA: %d", params->keystrokes[0]);
	mlx_string_put(mlx->ptr, mlx->win, 0, 0, 0x00FFFFFF, outputPosX);
	mlx_string_put(mlx->ptr, mlx->win, 0, 20, 0x00FFFFFF, outputPosY);
	mlx_string_put(mlx->ptr, mlx->win, 0, 40, 0x00FFFFFF, outputDirX);
	mlx_string_put(mlx->ptr, mlx->win, 0, 60, 0x00FFFFFF, outputDirY);
	mlx_string_put(mlx->ptr, mlx->win, 0, 80, 0x00FFFFFF, outputKeystrokesF);
	mlx_string_put(mlx->ptr, mlx->win, 0, 100, 0x00FFFFFF, outputKeystrokesB);
	mlx_string_put(mlx->ptr, mlx->win, 0, 120, 0x00FFFFFF, outputKeystrokesR);
	mlx_string_put(mlx->ptr, mlx->win, 0, 140, 0x00FFFFFF, outputKeystrokesL);
	mlx_string_put(mlx->ptr, mlx->win, 0, 160, 0x00FFFFFF, outputKeystrokesD);
	mlx_string_put(mlx->ptr, mlx->win, 0, 180, 0x00FFFFFF, outputKeystrokesA);

	return (0);
}

int			read_keys(t_data *params)
{
	t_player	*player;
	double		oldDirX;
	double		oldPlaneX;

	player = &params->player;

	// move forward if no wall in front of you
	if (params->keystrokes[13]) // Key W
	{
		if (worldMap[(int)(player->posX + player->dirX * player->moveSpeed)]
					[(int)(player->posY)] == 0 /*0 enum*/)
			// collision detection: won't move if it ain't 0 (a wall)
			player->posX += player->dirX * player->moveSpeed;
		if (worldMap[(int)(player->posX)]
					[(int)(player->posY + player->dirY * player->moveSpeed)] == 0)
			player->posY += player->dirY * player->moveSpeed;
	}

	// move backwards if no wall behind you
	if (params->keystrokes[1]) // Key S
	{
		if (worldMap[(int)(player->posX - player->dirX * player->moveSpeed)]
					[(int)(player->posY)] == 0)
			player->posX -= player->dirX * player->moveSpeed;
		if (worldMap[(int)(player->posX)]
					[(int)(player->posY - player->dirY * player->moveSpeed)] == 0)
			player->posY -= player->dirY * player->moveSpeed;
	}

	// move to the right if no wall is on the right
	if (params->keystrokes[2]) // Key D
	{
		if (worldMap[(int)(player->posX + player->planeX * player->moveSpeed)]
					[(int)(player->posY)] == 0 /*0 enum*/)
			player->posX += player->planeX * player->moveSpeed;
		if (worldMap[(int)(player->posX)]
					[(int)(player->posY + player->planeY * player->moveSpeed)] == 0)
			player->posY += player->planeY * player->moveSpeed;
	}

	// move to the left if no wall is on the left
	if (params->keystrokes[0]) // Key A
	{
		if (worldMap[(int)(player->posX - player->planeX * player->moveSpeed)]
					[(int)(player->posY)] == 0 /*0 enum*/)
			player->posX -= player->planeX * player->moveSpeed;
		if (worldMap[(int)(player->posX)]
					[(int)(player->posY - player->planeY * player->moveSpeed)] == 0)
			player->posY -= player->planeY * player->moveSpeed;
	}

	// rotate to the right
	if (params->keystrokes[124]) // Key arrow right
	{
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
	if (params->keystrokes[123]) // Key arrow left
	{
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
	if (keycode == 123 || keycode == 124 || keycode == 13 || keycode == 1 || keycode == 0 || keycode == 2 || keycode == 53)
	{
		params->keystrokes[keycode] = 1;
	}
	return (0);
}

int			key_release(int keycode, t_data *params)
{
	if (keycode == 123 || keycode == 124 || keycode == 13 || keycode == 1 || keycode == 0 || keycode == 2 || keycode == 53)
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
	player->planeX = 0,
	player->planeY = 0.66; // the 2d raycaster version of camera plane
	player->moveSpeed = 0.07;
	player->rotSpeed = 0.03;

	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, screenWidth, screenHeight, "cub3d");

	// generate some textures
	char *wallsFacingNorth = "../assets/textures/iron.xpm";
	char *wallsFacingSouth = "../assets/textures/grass.xpm";
	char *wallsFacingEast =	"../assets/textures/water.xpm";
	char *wallsFacingWest = "../assets/textures/gold.xpm";

	world->textures[NO] = loadImage(wallsFacingSouth, &params);
	world->textures[SO] = loadImage(wallsFacingNorth, &params);
	world->textures[EA] = loadImage(wallsFacingWest, &params);
	world->textures[WE] = loadImage(wallsFacingEast, &params);

	world->textures[4] = loadImage("../assets/textures/sprite-1.xpm", &params);
	world->textures[5] = loadImage("../assets/textures/sprite-2.xpm", &params);
	world->textures[6] = loadImage("../assets/textures/sprite-3.xpm", &params);

	img->img = mlx_new_image(mlx->ptr, screenWidth, screenHeight);
	img->addr = (int *)mlx_get_data_addr(
		img->img, &img->bits_per_pixel, &img->line_length, &img->endian);

	// this was the game loop that draws a whole frame and reads the input every time
	draw_frame(&params);

	// mlx_key_hook(mlx->win, read_keys, &params);
	mlx_hook(mlx->win, 2, 0, key_press, &params);
	mlx_hook(mlx->win, 3, 0, key_release, &params);
	mlx_loop_hook(mlx->ptr, read_keys, &params);
	mlx_loop(mlx->ptr);
}
