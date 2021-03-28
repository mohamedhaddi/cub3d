/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:40:14 by mhaddi            #+#    #+#             */
/*   Updated: 2021/03/28 14:48:11 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

#define screenWidth 640
#define screenHeight 480
#define mapWidth 24
#define mapHeight 24
// width and height in texels of the textures
#define texWidth 64
#define texHeight 64

typedef struct	s_img_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img_data;

typedef struct  s_mlx {
	void        *ptr;
	void        *win;
}               t_mlx;

typedef struct	s_player {
	double		dirX;	
	double		dirY;	
	double		posX;	
	double		posY;	
	double		planeX;	
	double		planeY;	
	double		moveSpeed;
	double		rotSpeed;
}				t_player;

typedef struct	s_world {
	int 		textures[8][texWidth * texHeight];
	// int			*textures;
  	uint32_t 	buffer[screenHeight][screenWidth]; // y-coordinate first because it works per scanline
} t_world;

typedef struct	s_data {
	t_img_data	img;
	t_mlx		mlx;
	t_player	player;
	t_world		world;
	int			keystroke[127];
}				t_data;

void			ft_mlx_pixel_put(t_img_data *img, int x, int y, int color);

#endif
