/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 21:35:54 by mhaddi            #+#    #+#             */
/*   Updated: 2021/01/29 01:09:41 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define mapWidth 24
#define mapHeight 24
#define screen_width 640
#define screen_height 480

t_mlx mlx;
t_img_data img;

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int read_keys(int keycode, t_player *player) {
  //65361 is left (enum later), and then clockwise
  //move forward if no wall in front of you
  if (keycode == 65362)
  {
	if(worldMap[(int)(player->posX + player->dirX * player->moveSpeed)][(int)(player->posY)] == 0 /*0 enum*/) player->posX += player->dirX * player->moveSpeed;
	if(worldMap[(int)(player->posX)][(int)(player->posY + player->dirY * player->moveSpeed)] == 0) player->posY += player->dirY * player->moveSpeed;
  }
  //move backwards if no wall behind you
  if (keycode == 65364)
  {
	if(worldMap[(int)(player->posX - player->dirX * player->moveSpeed)][(int)(player->posY)] == 0) player->posX -= player->dirX * player->moveSpeed;
	if(worldMap[(int)(player->posX)][(int)(player->posY - player->dirY * player->moveSpeed)] == 0) player->posY -= player->dirY * player->moveSpeed;
  }
  //rotate to the right
  if (keycode == 65363)
  {
	//both camera direction and camera plane must be rotated
	double oldDirX = player->dirX;
	player->dirX = player->dirX * cos(-player->rotSpeed) - player->dirY * sin(-player->rotSpeed);
	player->dirY = oldDirX * sin(-player->rotSpeed) + player->dirY * cos(-player->rotSpeed);
	double oldPlaneX = player->planeX;
	player->planeX = player->planeX * cos(-player->rotSpeed) - player->planeY * sin(-player->rotSpeed);
	player->planeY = oldPlaneX * sin(-player->rotSpeed) + player->planeY * cos(-player->rotSpeed);
  }
  //rotate to the left
  if (keycode == 65361)
  {
	//both camera direction and camera plane must be rotated
	double oldDirX = player->dirX;
	player->dirX = player->dirX * cos(player->rotSpeed) - player->dirY * sin(player->rotSpeed);
	player->dirY = oldDirX * sin(player->rotSpeed) + player->dirY * cos(player->rotSpeed);
	double oldPlaneX = player->planeX;
	player->planeX = player->planeX * cos(player->rotSpeed) - player->planeY * sin(player->rotSpeed);
	player->planeY = oldPlaneX * sin(player->rotSpeed) + player->planeY * cos(player->rotSpeed);
  }
  return 0;
}

int loop(t_player *player) {
    //here starts the raycasting loop 
    for (int x = 0; x < screen_width; x++) {
      //calculate ray position and direction
      double cameraX = 2 * x / (double)screen_width - 1; //x-coordinate in camera space
      double rayDirX = player->dirX + player->planeX * cameraX;
      double rayDirY = player->dirY + player->planeY * cameraX;

      //which box of the map we're in
      int mapX = (int)player->posX;
      int mapY = (int)player->posY;

      //length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY;

      //length of ray from one x or y-side to next x or y-side
      ///double deltaDistX = fabs(1 / rayDirX);
      //double deltaDistY = fabs(1 / rayDirY);
      // Alternative code for deltaDist in case division through zero is not supported
      double deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : fabs(1 / rayDirX));
      double deltaDistY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : fabs(1 / rayDirY));
      double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?

	  //calculate step and initial sideDist
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

      //perform DDA
      //a loop that increments the ray with 1 square every time until a wall is hit
      while (hit == 0)
      {
        //jump to next map square, OR in x-direction, OR in y-direction
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
        //Check if ray has hit a wall
        if (worldMap[mapX][mapY] > 0) hit = 1;
      } 	
      //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
      if (side == 0) perpWallDist = (mapX - player->posX + (1.0 - stepX) / 2) / rayDirX;
      else           perpWallDist = (mapY - player->posY + (1.0 - stepY) / 2) / rayDirY;

      //Calculate height of line to draw on screen
      int lineHeight = (int)(screen_height / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + screen_height / 2;
      if(drawStart < 0)drawStart = 0;
      int drawEnd = lineHeight / 2 + screen_height / 2;
      if(drawEnd >= screen_height)drawEnd = screen_height - 1;
      
      //choose wall color
      int color;
      switch(worldMap[mapX][mapY])
      {
        case 1:  color = 0x00FF0000;  break; //red
        case 2:  color = 0x0000FF00;  break; //green
        case 3:  color = 0x000000FF;  break; //blue
        case 4:  color = 0x00FFFFFF;  break; //white
        default: color = 0x0000FFFF;  break; //yellow
      }

      //give x and y sides different brightness
      if (side == 1) {color = color / 2;}

      //draw the pixels of the stripe as a vertical line
      //verLine(x, drawStart, drawEnd, color);
      for (int y = drawStart; y <= drawEnd; y++) {
        ft_mlx_pixel_put(&img, x, y, color);
      }
    }
    mlx_put_image_to_window(mlx.ptr, mlx.win, img.img, 0, 0);

	for (int x = 0; x <= screen_width; x++) {
      for (int y = 0; y <= screen_height; y++) {
        ft_mlx_pixel_put(&img, x, y, 0x00000000);
      }
	}
	//player->moveSpeed = 0.2; //frame_time * 5.0; // the constant value is squares / second
	//player->rotSpeed = 0.03; //frame_time * 3.0; // the constant value is in radian / second
    return 0;
}

int main() {
  //int done = 0;

  t_player player;
  player.posX = 22, player.posY = 12;  //x and y start position of the player
  player.dirX = -1, player.dirY = 0; //initial direction vector
  player.planeX = 0, player.planeY = 0.66; //the 2d raycaster version of camera plane
  player.moveSpeed = 0.2;
  player.rotSpeed = 0.06;

  //double time = 0; //time of current frame
  //double oldTime = 0; //time of previous frame

  mlx.ptr = mlx_init();
  mlx.win = mlx_new_window(mlx.ptr, screen_width, screen_height, "cub3d");
  img.img = mlx_new_image(mlx.ptr, screen_width, screen_height);
  img.addr = mlx_get_data_addr(
      img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

  /***/
  //this is where the magic happens
  //this is the loop that draws a whole frame and reads the input every time
  mlx_loop_hook(mlx.ptr, loop, &player);
  /***/

  mlx_key_hook(mlx.win, read_keys, &player);
  mlx_loop(mlx.ptr);
}

