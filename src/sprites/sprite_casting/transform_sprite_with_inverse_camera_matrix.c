/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_sprite_with_inverse_camera_matr          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:31:19 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 23:31:18 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/**
 * transform sprite with the inverse camera matrix
 * [planeX dirX] -1                                 [dirY     -dirX]
 * [           ]    = 1/(planeX*dirY-dirX*planeY) * [              ]
 * [planeY dirY]                                    [-planeY planeX]
 * - `inv_det` required for correct matrix multiplication
 * - `sprite->transform.y` is actually the depth inside the screen,
 * that what z is in 3D
 */
void	transform_sprite_with_inverse_camera_matrix(t_sprite *sprite,
													t_resolution *resolution,
													t_player *player)
{
	double	inv_det;

	inv_det = 1.0 / (player->plane.x
			* player->dir.y - player->dir.x
			* player->plane.y);
	sprite->transform.x = inv_det * (player->dir.y
			* sprite->pos.x - player->dir.x
			* sprite->pos.y);
	sprite->transform.y = inv_det
		* (-player->plane.y
			* sprite->pos.x + player->plane.x
			* sprite->pos.y);
	sprite->screen_x = (int)
		(((double)resolution->width / 2)
			* (1 + sprite->transform.x / sprite->transform.y));
}
