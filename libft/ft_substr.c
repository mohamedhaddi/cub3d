/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:15:13 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/23 17:54:25 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			j;
	char			*substr;
	size_t			slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start > slen || !len || !*s)
		return (ft_strdup(""));
	j = 0;
	if (len > slen - start)
		len = slen - start;
	substr = malloc((sizeof(*substr) * len) + sizeof(*substr));
	if (!substr)
		return (NULL);
	s += start;
	while (*s && j < len)
		substr[j++] = *(s++);
	substr[j] = '\0';
	return (substr);
}
