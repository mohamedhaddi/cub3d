/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 17:14:31 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/29 09:47:03 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

char	*save_texture(char **texture, bool *presence)
{
	char		*texture_path;
	static int	tex_num;
	int			i;

	if (tex_num > 4)
		ft_error(NULL, "Error\nDuplicate texture");
	tex_num++;
	i = 1;
	while (texture[i])
		i++;
	if (i != 2)
		ft_error(NULL, "Error\nTexture information is incorrect\n");
	texture_path = ft_strdup(texture[1]);
	free_double_pointer(texture);
	*presence = true;
	i = 0;
	while (texture_path[i])
	{
		texture_path[i] = ft_tolower(texture_path[i]);
		i++;
	}
	return (texture_path);
}
