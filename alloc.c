/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 15:54:00 by eviana            #+#    #+#             */
/*   Updated: 2019/06/19 16:52:28 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		alloc_rooms(t_data *data)
{
    t_room  *rooms;

	if (!(rooms = (t_room *)malloc(sizeof(t_room) * data->nb_rooms)))
		return (0);
	data->rooms = rooms;
	return (1);
}

int		**alloc_matrix_int(int	x, int y, int val)
{
	int		i;
	int		j;
	int		**mx;

	i = 0;
	if (!(mx = (int**)malloc(sizeof(int*) * y)))
		return (NULL);
	while (i < y)
	{
		j = 0;
		if (!(mx[i] = (int*)malloc(sizeof(int) * x)))
			return (NULL);
		while (j < x)
			mx[i][j++] = val;
		i++;
	}
	return (mx);
}