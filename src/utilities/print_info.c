/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:59:56 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 17:12:51 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

typedef struct	s_strings
{
	char		*output_pos_x;
	char		*output_pos_y;
	char		*output_dir_x;
	char		*output_dir_y;
	char		*output_keystrokes_f;
	char		*output_keystrokes_b;
	char		*output_keystrokes_r;
	char		*output_keystrokes_l;
	char		*output_keystrokes_d;
	char		*output_keystrokes_a;
}				t_strings;

t_strings		strings;

void			alloc_strings()
{
	strings.output_pos_x = (char *)malloc(20 * sizeof(char));
	strings.output_pos_y = (char *)malloc(20 * sizeof(char));
	strings.output_dir_x = (char *)malloc(20 * sizeof(char));
	strings.output_dir_y = (char *)malloc(20 * sizeof(char));
	strings.output_keystrokes_f = (char *)malloc(20 * sizeof(char));
	strings.output_keystrokes_b = (char *)malloc(20 * sizeof(char));
	strings.output_keystrokes_r = (char *)malloc(20 * sizeof(char));
	strings.output_keystrokes_l = (char *)malloc(20 * sizeof(char));
	strings.output_keystrokes_d = (char *)malloc(20 * sizeof(char));
	strings.output_keystrokes_a = (char *)malloc(20 * sizeof(char));
}

void			set_values(t_player *player, t_data *params)
{
	sprintf(strings.output_pos_x, "pos_x: %f", player->pos.x);
	sprintf(strings.output_pos_y, "pos_y: %f", player->pos.y);
	sprintf(strings.output_dir_x, "dir_x: %f", player->dir.x);
	sprintf(strings.output_dir_y, "dir_y: %f", player->dir.y);
	sprintf(strings.output_keystrokes_f, "key_w: %d", params->keystrokes[13]);
	sprintf(strings.output_keystrokes_b, "key_s: %d", params->keystrokes[1]);
	sprintf(strings.output_keystrokes_r, "key_r: %d", params->keystrokes[124]);
	sprintf(strings.output_keystrokes_l, "key_l: %d", params->keystrokes[123]);
	sprintf(strings.output_keystrokes_d, "key_d: %d", params->keystrokes[2]);
	sprintf(strings.output_keystrokes_a, "key_a: %d", params->keystrokes[0]);
}

void			put_strings_into_frame(t_mlx *mlx)
{
	mlx_string_put(mlx->ptr, mlx->win, 0, 0, 0x00FFFFFF, strings.output_pos_x);
	mlx_string_put(mlx->ptr, mlx->win, 0, 20, 0x00FFFFFF, strings.output_pos_y);
	mlx_string_put(mlx->ptr, mlx->win, 0, 40, 0x00FFFFFF, strings.output_dir_x);
	mlx_string_put(mlx->ptr, mlx->win, 0, 60, 0x00FFFFFF, strings.output_dir_y);
	mlx_string_put(
		mlx->ptr, mlx->win, 0, 80, 0x00FFFFFF, strings.output_keystrokes_f);
	mlx_string_put(
		mlx->ptr, mlx->win, 0, 100, 0x00FFFFFF, strings.output_keystrokes_b);
	mlx_string_put(
		mlx->ptr, mlx->win, 0, 120, 0x00FFFFFF, strings.output_keystrokes_r);
	mlx_string_put(
		mlx->ptr, mlx->win, 0, 140, 0x00FFFFFF, strings.output_keystrokes_l);
	mlx_string_put(
		mlx->ptr, mlx->win, 0, 160, 0x00FFFFFF, strings.output_keystrokes_d);
	mlx_string_put(
		mlx->ptr, mlx->win, 0, 180, 0x00FFFFFF, strings.output_keystrokes_a);
}

/**
 * show real-time values for cetain variables on screen
 * to-remove later (because forbidden function sprintf)
 */
void			print_info(t_player *player, t_data *params)
{
	t_mlx	*mlx;

	mlx = &params->mlx;
	set_values(player, params);
	put_strings_into_frame(mlx);
}
