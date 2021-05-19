/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:25:43 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 19:33:11 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_buffer(t_resolution *resolution,
					t_world *world,
					t_img_data *img,
					t_mlx *mlx)
{
	int	x;
	int	y;

	x = 0;
	while (x < resolution->width)
	{
		y = 0;
		while (y < resolution->height)
		{
			ft_mlx_pixel_put(img, x, y, world->buffer[y][x]);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win, img->img, 0, 0);
}
