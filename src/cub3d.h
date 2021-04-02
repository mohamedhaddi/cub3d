/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:40:14 by mhaddi            #+#    #+#             */
/*   Updated: 2021/04/02 15:08:12 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define screenWidth 640
# define screenHeight 480
# define mapWidth 24
# define mapHeight 24
# define texSize 64
# define numSprites 19

typedef struct	s_img_data
{
	void		*img;
	int			*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img_data;

typedef struct	s_texture {
	t_img_data	texture_img_data;
	int			width;
	int			height;
}				t_texture;

typedef struct	s_mlx
{
	void		*ptr;
	void		*win;
}				t_mlx;

typedef struct	s_player
{
	double		dirX;
	double		dirY;
	double		posX;
	double		posY;
	double		planeX;
	double		planeY;
	double		moveSpeed;
	double		rotSpeed;
}				t_player;

typedef struct	s_sprite
{
  double		x;
  double 		y;
  int 			texture;
}				t_sprite;

typedef struct	s_world
{
	t_texture	textures[8];
	int			buffer[screenHeight][screenWidth];
	// t_sprite	sprites[numSprites];
	//1D Zbuffer
	double		ZBuffer[screenWidth];
	//arrays used to sort the sprites
	int			spriteOrder[numSprites];
	double		spriteDistance[numSprites];
}				t_world;

typedef struct	s_data
{
	t_img_data	img;
	t_mlx		mlx;
	t_player	player;
	t_world		world;
	int			keystrokes[127];
}				t_data;

void			ft_mlx_pixel_put(t_img_data *img, int x, int y, int color);

void			sort_sprites(int *order, double *dist, int amount);

#endif
