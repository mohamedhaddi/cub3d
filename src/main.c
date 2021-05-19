/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 21:35:54 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 19:04:18 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <time.h>

int				main()
{
	t_data		params;
	t_mlx		*mlx;
	t_img_data	*img;

	mlx = &params.mlx;
	img = &params.img;
	srand(time(NULL));
	alloc_strings();
	set_screen_resolution(&params);
	set_map_size(&params);
	generate_world_map(&params);
	load_mlx(&params);
	load_game(&params);
	draw_frame(&params);
	mlx_loop_hook(mlx->ptr, read_keys, &params);
	mlx_hook(mlx->win, 2, 1L, key_press, &params);
	mlx_hook(mlx->win, 3, 2L, key_release, &params);
	mlx_hook(mlx->win, 17, 1L, red_cross_press, &params);
	mlx_loop(mlx->ptr);
}
