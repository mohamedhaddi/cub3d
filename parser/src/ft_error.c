/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 17:12:48 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/21 17:12:50 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	raise_map_error(char **map, int i, int j)
{
	char	*row;
	char	*col;

	row = ft_itoa(i);
	col = ft_itoa(j);
	ft_putstr_fd("Error\nMap error in row ", 2);
	ft_putstr_fd(row, 2);
	ft_putstr_fd(" column ", 2);
	ft_putstr_fd(col, 2);
	free(row);
	free(col);
	free_memory(map, EXIT_FAILURE);
}

void	ft_error(char **map, char *error)
{
	ft_putstr_fd(error, 2);
	free_memory(map, EXIT_FAILURE);
}
