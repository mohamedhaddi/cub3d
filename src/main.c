/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 21:35:54 by mhaddi            #+#    #+#             */
/*   Updated: 2021/03/28 17:54:31 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx/mlx.h"


int worldMap[mapWidth][mapHeight] = {
    {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7, 7, 7, 7, 7, 7, 7, 7},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7},
    {4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
    {4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
    {4, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7},
    {4, 0, 4, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 0, 7, 7, 7, 7, 7},
    {4, 0, 5, 0, 0, 0, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 7, 0, 0, 0, 7, 7, 7, 1},
    {4, 0, 6, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0, 8},
    {4, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 1},
    {4, 0, 8, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0, 8},
    {4, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 7, 7, 7, 1},
    {4, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 0, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 1},
    {6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
    {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
    {6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
    {4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 6, 0, 6, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 2, 0, 0, 5, 0, 0, 2, 0, 0, 0, 2},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2},
    {4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 6, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 2},
    {4, 0, 0, 5, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2},
    {4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 5, 0, 0, 2, 0, 0, 0, 2},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2},
    {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3}};

/**
 * test
 */

int draw_frame(t_data *params) {
  t_mlx *mlx;
  t_img_data *img;
  t_player *player;
  t_world *world;
  double rayDirX;
  double rayDirY;
  int mapX;
  int mapY;
  double sideDistX;
  double sideDistY;
  double perpWallDist;
  int stepX;
  int stepY;
  int lineHeight;
  int drawStart;
  int drawEnd;
  //int color;
  double deltaDistX;
  double deltaDistY;

  mlx = &params->mlx;
  img = &params->img;
  player = &params->player;
  world = &params->world;
  // here starts the raycasting loop
  for (int x = 0; x < screenWidth; x++) {
    // calculate ray position and direction
    double cameraX =
        2 * x / (double)screenWidth - 1; // x-coordinate in camera space
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
    /*
    double deltaDistX =
            (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : fabs(1 / rayDirX));
    double deltaDistY =
            (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : fabs(1 / rayDirY));
    */
    deltaDistX = fabs(1 / rayDirX);
    deltaDistY = fabs(1 / rayDirY);
    // what direction to step in x or y-direction (either +1 or -1)
    int hit = 0; // was there a wall hit?
    int side;    // was a NS or a EW wall hit?
    // calculate step and initial sideDist
    if (rayDirX < 0) {
      stepX = -1;
      sideDistX = (player->posX - mapX) * deltaDistX;
    } else {
      stepX = 1;
      sideDistX = (mapX + 1.0 - player->posX) * deltaDistX;
    }
    if (rayDirY < 0) {
      stepY = -1;
      sideDistY = (player->posY - mapY) * deltaDistY;
    } else {
      stepY = 1;
      sideDistY = (mapY + 1.0 - player->posY) * deltaDistY;
    }
    // perform DDA
    // a loop that increments the ray with 1 square every time until a wall
    // is hit
    while (hit == 0) {
      // jump to next map square, OR in x-direction, OR in y-direction
      if (sideDistX < sideDistY) {
        sideDistX += deltaDistX;
        mapX += stepX;
        side = 0;
      } else {
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
    lineHeight = (int)(screenHeight / perpWallDist);
    // calculate lowest and highest pixel to fill in current stripe
    drawStart = -lineHeight / 2 + screenHeight / 2;
    if (drawStart < 0)
      drawStart = 0;
    drawEnd = lineHeight / 2 + screenHeight / 2;
    if (drawEnd >= screenHeight)
      drawEnd = screenHeight - 1;
    // choose wall color
    /*
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
    // give x and y sides different brightness (if a y-side was hit, make the
    color darker) if (side == 1)
    {
            color = color / 2;
    }
    // draw the pixels of the stripe as a vertical line
    // verLine(x, drawStart, drawEnd, color);
    for (int y = drawStart; y <= drawEnd; y++)
    {
            ft_mlx_pixel_put(img, x, y, color);
    }
    */

    // texturing calculations
    int texNum = worldMap[mapX][mapY] -
                 1; // 1 subtracted from it so that texture 0 can be used!

    // calculate value of wallX
    double wallX; // where exactly the wall was hit
    if (side == 0)
      wallX = player->posY + perpWallDist * rayDirY;
    else
      wallX = player->posX + perpWallDist * rayDirX;
    wallX -= floor((wallX));

    // x coordinate on the texture
    int texX = (int)(wallX * (double)texWidth);
    if (side == 0 && rayDirX > 0)
      texX = texWidth - texX - 1;
    if (side == 1 && rayDirY < 0)
      texX = texWidth - texX - 1;

    // How much to increase the texture coordinate per screen pixel
    double step = 1.0 * texHeight / lineHeight;
    // Starting texture coordinate
    double texPos = ((double)drawStart - (double)screenHeight / 2 + (double)lineHeight / 2) * step;
    for (int y = drawStart; y < drawEnd; y++) {
      // Cast the texture coordinate to integer, and mask with (texHeight - 1)
      // in case of overflow
      int texY = (int)texPos & (texHeight - 1);
      texPos += step;
      uint32_t color = world->textures[texNum][texHeight * texY + texX];
      // make color darker for y-sides: R, G and B byte each divided through two
      // with a "shift" and an "and"
      if (side == 1)
        color = (color >> 1) & 8355711;
      world->buffer[y][x] = color;
    }
  }

  // printf("before drawing\n");
  for (int x = 0; x < screenWidth; x++) {
    for (int y = 0; y < screenHeight; y++) {
      // printf("%d\n", world->buffer[y][x]);
      ft_mlx_pixel_put(img, x, y, world->buffer[y][x]);
    }
  }

  mlx_put_image_to_window(mlx->ptr, mlx->win, img->img, 0, 0);

  char *sPosX = (char *)malloc(20 * sizeof(char));
  char *sPosY = (char *)malloc(20 * sizeof(char));
  char *sDirX = (char *)malloc(20 * sizeof(char));
  char *sDirY = (char *)malloc(20 * sizeof(char));
  sprintf(sPosX, "posX: %f", player->posX);
  sprintf(sPosY, "posY: %f", player->posY);
  sprintf(sDirX, "dirX: %f", player->dirX);
  sprintf(sDirY, "dirY: %f", player->dirY);
  mlx_string_put(mlx->ptr, mlx->win, 0, 0, 0x00FFFFFF, sPosX);
  mlx_string_put(mlx->ptr, mlx->win, 0, 20, 0x00FFFFFF, sPosY);
  mlx_string_put(mlx->ptr, mlx->win, 0, 40, 0x00FFFFFF, sDirX);
  mlx_string_put(mlx->ptr, mlx->win, 0, 60, 0x00FFFFFF, sDirY);

  // clear
  for (int x = 0; x < screenWidth; x++) {
    for (int y = 0; y < screenHeight; y++) {
      //ft_mlx_pixel_put(img, x, y, 0x00000000);
      world->buffer[y][x] = 0;
    }
  }
  return (0);
}

int read_keys(t_data *params) {
  t_player *player;
  double oldDirX;
  double oldPlaneX;

  player = &params->player;
  // move forward if no wall in front of you
  if (params->keystroke[126]) {
    /*
    printf("posX: %f\nposY: %f\ndirX: %f\ndirY: %f\n\n",
                    player->posX,
                    player->posY,
                    player->dirX,
                    player->dirY);
    */
    if (worldMap[(int)(player->posX + player->dirX * player->moveSpeed)]
                [(int)(player->posY)] == 0 /*0 enum*/)
      // collision detection: won't move if it ain't 0 (a wall)
      player->posX += player->dirX * player->moveSpeed;
    if (worldMap[(int)(player->posX)]
                [(int)(player->posY + player->dirY * player->moveSpeed)] == 0)
      player->posY += player->dirY * player->moveSpeed;
  }
  // move backwards if no wall behind you
  if (params->keystroke[125]) {
    /*
    printf("posX: %f\nposY: %f\ndirX: %f\ndirY: %f\n\n",
                    player->posX,
                    player->posY,
                    player->dirX,
                    player->dirY);
    */
    if (worldMap[(int)(player->posX - player->dirX * player->moveSpeed)]
                [(int)(player->posY)] == 0)
      player->posX -= player->dirX * player->moveSpeed;
    if (worldMap[(int)(player->posX)]
                [(int)(player->posY - player->dirY * player->moveSpeed)] == 0)
      player->posY -= player->dirY * player->moveSpeed;
  }
  // rotate to the right
  if (params->keystroke[124]) {
    /*
    printf("posX: %f\nposY: %f\ndirX: %f\ndirY: %f\n\n",
                    player->posX,
                    player->posY,
                    player->dirX,
                    player->dirY);
    */
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
  if (params->keystroke[123]) {
    /*
    printf("posX: %f\nposY: %f\ndirX: %f\ndirY: %f\n\n",
                    player->posX,
                    player->posY,
                    player->dirX,
                    player->dirY);
    */
    // both camera direction and camera plane must be rotated
    oldDirX = player->dirX;
    player->dirX = player->dirX * cos(player->rotSpeed) -
                   player->dirY * sin(player->rotSpeed);
    player->dirY =
        oldDirX * sin(player->rotSpeed) + player->dirY * cos(player->rotSpeed);
    oldPlaneX = player->planeX;
    player->planeX = player->planeX * cos(player->rotSpeed) -
                     player->planeY * sin(player->rotSpeed);
    player->planeY = oldPlaneX * sin(player->rotSpeed) +
                     player->planeY * cos(player->rotSpeed);
  }
  draw_frame(params);
  return (0);
}

int key_press(int keycode, t_data *params) {
  if (keycode == 123 || keycode == 124 || keycode == 125 || keycode == 126) {
    params->keystroke[keycode] = 1;
  }
  return (0);
}

int key_release(int keycode, t_data *params) {
  if (keycode == 123 || keycode == 124 || keycode == 125 || keycode == 126) {
    params->keystroke[keycode] = 0;
  }
  return (0);
}

int main() {
  t_data params;
  t_mlx *mlx;
  t_img_data *img;
  t_player *player;
  t_world *world;

  mlx = &params.mlx;
  img = &params.img;
  player = &params.player;
  world = &params.world;
  // memset(params.keystroke, 0, 127);
  params.keystroke[126] = 0;
  params.keystroke[125] = 0;
  params.keystroke[124] = 0;
  params.keystroke[123] = 0;
  player->posX = 22, player->posY = 12; // x and y start position of the player
  player->dirX = -1, player->dirY = 0;  // initial direction vector
  player->planeX = 0,
  player->planeY = 0.66; // the 2d raycaster version of camera plane
  player->moveSpeed = 0.07;
  player->rotSpeed = 0.03;

  /*
  int *texture[8];
  for (int i = 0; i < 8; i++) {
    texture[i] = malloc(sizeof(*texture) * texWidth * texHeight);
    // texture[i].resize(texWidth * texHeight);
  }
  */
  // int texture[8][texWidth * texHeight];

  mlx->ptr = mlx_init();
  mlx->win = mlx_new_window(mlx->ptr, screenWidth, screenHeight, "cub3d");

  // generate some textures
  for (int x = 0; x < texWidth; x++) {
    for (int y = 0; y < texHeight; y++) {
      int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
      // int xcolor = x * 256 / texWidth;
      int ycolor = y * 256 / texHeight;
      int xycolor = y * 128 / texHeight + x * 128 / texWidth;
      world->textures[0][texWidth * y + x] =
          65536 * 254 *
          (x != y && x != texWidth - y); // flat red texture with black cross
      world->textures[1][texWidth * y + x] =
          xycolor + 256 * xycolor + 65536 * xycolor; // sloped greyscale
      world->textures[2][texWidth * y + x] =
          256 * xycolor + 65536 * xycolor; // sloped yellow gradient
      world->textures[3][texWidth * y + x] =
          xorcolor + 256 * xorcolor + 65536 * xorcolor; // xor greyscale
      world->textures[4][texWidth * y + x] = 256 * xorcolor;    // xor green
      world->textures[5][texWidth * y + x] =
          65536 * 192 * (x % 16 && y % 16);          // red bricks
      world->textures[6][texWidth * y + x] = 65536 * ycolor; // red gradient
      world->textures[7][texWidth * y + x] =
          128 + 256 * 128 + 65536 * 128; // flat grey texture
    }
  }

  img->img = mlx_new_image(mlx->ptr, screenWidth, screenHeight);
  img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
                                &img->line_length, &img->endian);

  // this was the game loop that draws a whole frame and reads the input every
  // time
  draw_frame(&params);
  // mlx_key_hook(mlx->win, read_keys, &params);
  mlx_hook(mlx->win, 2, 0, key_press, &params);
  mlx_hook(mlx->win, 3, 0, key_release, &params);
  mlx_loop_hook(mlx->ptr, read_keys, &params);
  // mlx_do_key_autorepeaton(mlx->ptr);
  mlx_loop(mlx->ptr);
}
