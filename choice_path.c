/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choice_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 17:34:46 by eviana            #+#    #+#             */
/*   Updated: 2019/08/01 16:54:41 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int     count_size(char *str, int flow)
{
    int     i;
    int     j;

    i = 0;
    j = 0;
    while (i < flow + 1)
    {
        if (str[j++] == '\n')
            i++;
    }
    i = 0;
    while (str[j] && str[j] != '\n')
    {
        j++;
        i++;
    }
    return (i);
}
/*
int    choice_path(t_data *data, t_path *path)
{
    int     flow;
    int     i;
    int     nb_ants;
    int     diff;
    int     size;

    nb_ants = data->nb_ants;
    flow = 0;
    i = 0;
    if (!(data->score = (int*)malloc(sizeof(int) * (data->flow_max + 1))))
        return (0);
    while (flow < data->flow_max + 1)
    {
        data->score[flow] = 0;
        i = 0;
        diff = 0;
        while (i <= flow)
        {
            size = count_size(path->paths, i);
            while ((nb_ants + diff) % (flow + 1) != 0)
                diff++;
            ft_putnbr(data->score[flow] = ((nb_ants + diff) / (flow + 1)) + size -1 + data->score[flow]);
            ft_putchar('\n');
            if (path->next)
                path = path->next;
            i++;
        }
        flow++;
    }
    return (0);
}*/