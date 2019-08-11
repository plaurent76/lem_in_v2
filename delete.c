/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 16:34:29 by eviana            #+#    #+#             */
/*   Updated: 2019/06/20 16:42:17 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_strtabdel(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		ft_strdel(&str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

void	ft_inttabdel(int **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
        tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}