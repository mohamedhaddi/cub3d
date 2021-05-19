/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 15:05:38 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/19 22:50:44 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	swap(t_pair *xp, t_pair *yp)
{
	t_pair	temp;

	temp = *xp;
	*xp = *yp;
	*yp = temp;
}

static void	pair_sort(t_pair arr[], int n)
{
	int	i;
	int	j;

	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (arr[j].first > arr[j + 1].first)
				swap(&arr[j], &arr[j + 1]);
			j++;
		}
		i++;
	}
}

/**
 * initializes an array of two pairs with distance as the first pair then order
 * as the second one the sorts that collection of pairs in reverse order so we
 * can draw sprites from farthest to nearest
 */
void	sort_sprites(int *order, double *dist, int amount)
{
	t_pair	*sprites;
	int		i;

	sprites = malloc(sizeof(*sprites) * amount);
	i = 0;
	while (i < amount)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
		i++;
	}
	pair_sort(sprites, amount);
	i = 0;
	while (i < amount)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
		i++;
	}
	free(sprites);
}
