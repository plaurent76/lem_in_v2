/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 18:06:23 by plaurent          #+#    #+#             */
/*   Updated: 2019/05/29 18:01:12 by plaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	free_tab(char ***tab)
{
	int i;

	i = 0;
	while ((*tab)[i] != NULL)
		free((*tab)[i++]);
	free(*tab);
	*tab = NULL;
}

void	ft_inttabdel(int ***tab)
{
	int i;

	i = 0;
	while ((*tab)[i] != NULL)
	{
		free((*tab)[i]);
		i++;
	}
	free(*tab);
	*tab = NULL;
}

void	last_free(char **map, char **piece, char *line, int **heat_map)
{
	if (map != NULL)
		free_tab(&map);
	if (piece != NULL)
		free_tab(&piece);
	if (line != NULL)
		ft_strdel(&line);
	if (heat_map != NULL)
		ft_inttabdel(&heat_map);
}
