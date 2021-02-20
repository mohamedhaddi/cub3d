/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:40:14 by mhaddi            #+#    #+#             */
/*   Updated: 2021/02/01 23:39:04 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <mlx_int.h>
# include <math.h>
# include <string.h>

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

typedef struct	s_data {
	t_img_data	img;
	t_mlx		mlx;
	t_player	player;
	int			keystroke[65365];
}				t_data;

void			ft_mlx_pixel_put(t_img_data *img, int x, int y, int color);

#endif
