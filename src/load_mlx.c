/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:34:10 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 19:29:44 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_mlx(t_data *params)
{
	t_mlx		*mlx;
	t_img_data	*img;

	mlx = &params->mlx;
	img = &params->img;
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(
		mlx->ptr, params->resolution.width, params->resolution.height, "cub3d");
	img->img = mlx_new_image(
		mlx->ptr, params->resolution.width, params->resolution.height);
	img->addr = (int *)mlx_get_data_addr(
		img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
}
