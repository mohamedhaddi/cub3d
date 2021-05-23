/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 06:39:19 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/23 16:26:50 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*current;
	t_list	*newnode;

	if (lst && f)
	{
		current = lst;
		newlist = ft_lstnew(f(current->content));
		while (current->next)
		{
			current = current->next;
			newnode = ft_lstnew(f(current->content));
			if (!newnode)
			{
				ft_lstclear(&newlist, del);
				return (NULL);
			}
			ft_lstadd_back(&newlist, newnode);
		}
		return (newlist);
	}
	else
		return (NULL);
}
