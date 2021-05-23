/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 00:22:02 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/23 16:24:50 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	t_list	*temp;

	if (new)
	{
		temp = *alst;
		*alst = new;
		(*alst)->next = temp;
	}
	else
		*alst = new;
}
