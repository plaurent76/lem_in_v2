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

int		**alloc_matrix(int x, int y, int id)
{
	int		i;
	int		j;
	int		**matrix;
	
	i = 0;
	if (!(matrix = (int**)malloc(sizeof(int*) * y)))
		return (NULL);
	while (i < y)
	{
		j = 0;
		if (!(matrix[i] = (int*)malloc(sizeof(int) * x)))
			return (NULL);
		while (j < x)
			matrix[i][j++] = id;
		i++;
	}
	return (matrix);
}