/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_pixel_put.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 00:44:50 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 19:53:24 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_mlx_pixel_put(t_img_data *img, int x, int y, int color)
{
	char	*pixel;

	pixel = (char *)img->addr + (y * img->line_length
			+ x * (img->bits_per_pixel / 8));
	*(int *)pixel = color;
}
