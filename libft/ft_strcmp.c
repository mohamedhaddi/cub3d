/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 17:18:56 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/21 17:19:04 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(const char *x, const char *y)
{
	while (*x)
	{
		if (*x != *y)
			break ;
		x++;
		y++;
	}
	return (*(const unsigned char*)x - *(const unsigned char*)y);
}
