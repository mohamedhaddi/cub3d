/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 17:10:51 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/21 17:10:57 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define MAXINT 2147483647
# include <stdlib.h>
# include <unistd.h>
# define BUFFER_SIZE 32

int			get_next_line(int fd, char **line);
void		*ft_char_calloc(size_t i);
size_t		ft_strlen(const char *s);
char		*ft_strcpy(char *dest, const char *src);
#endif
