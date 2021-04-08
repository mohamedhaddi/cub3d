/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 17:41:34 by mhaddi            #+#    #+#             */
/*   Updated: 2021/04/07 17:42:34 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    ft_putstr_fd(char *s, int fd)
{
    int i;

    if (!s)
        return ;
    i = 0;
    while (*(s + i) != '\0')
    {
        write(fd, (s + i), 1);
        i++;
    }
}