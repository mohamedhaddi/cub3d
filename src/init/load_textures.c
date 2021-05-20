/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:46:15 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/20 01:20:29 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_img_data	load_image(char *path, t_data *params)
{
	t_img_data	texture_buffer;
	t_mlx		*mlx;

	mlx = &params->mlx;
	texture_buffer.img = mlx_xpm_file_to_image(mlx->ptr,
			path,
			&texture_buffer.width,
			&texture_buffer.height);
	if (texture_buffer.img == NULL || texture_buffer.width != TEX_SIZE
		|| texture_buffer.height != TEX_SIZE)
	{
		ft_putstr_fd("Error\n Invalid texture", 2);
		exit_game(params, EXIT_SUCCESS);
	}
	texture_buffer.addr = (int *)mlx_get_data_addr(texture_buffer.img,
			&texture_buffer.bits_per_pixel,
			&texture_buffer.line_length,
			&texture_buffer.endian);
	return (texture_buffer);
}

void	load_textures(t_data *params)
{
	t_world	*world;

	world = &params->world;
	world->textures = malloc(sizeof(*world->textures) * TEX_NUM);
	world->textures[NO] = load_image(
			world->texture_paths.walls_facing_south,
			params);
	world->textures[SO] = load_image(
			world->texture_paths.walls_facing_north,
			params);
	world->textures[EA] = load_image(
			world->texture_paths.walls_facing_west,
			params);
	world->textures[WE] = load_image(
			world->texture_paths.walls_facing_east,
			params);
	world->textures[SPRITE_INDEX] = load_image(
			world->texture_paths.sprite,
			params);
}
