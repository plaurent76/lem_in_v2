/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 12:57:06 by eviana            #+#    #+#             */
/*   Updated: 2019/08/01 17:22:11 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void    next_queue(t_data *data, int *queue) // Peut etre optimise avec la variable j de bfs
{
    size_t  i;

    i = 0;
    while (i + 1 < data->nb_rooms)
    {
        queue[i] = queue[i + 1];
        i++;
    }
}

int       *bfs(t_data *data, int **matrix) // le param "res" peut etre retire
{
    int         **tmp_matrix;
    int         *queue;
    int         *path;
    int         deadlock;
    int         i;
    int         j;

    ft_printf("        --- BFS ---        \n");//TEST
    deadlock = 1;
    if (!(path = ft_tabset(data->nb_rooms, -1)))
        return (NULL);
    if (!(tmp_matrix = ft_matrixdup(matrix, data->nb_rooms)))
        return (NULL);
    if (!data->block && !(data->block = ft_tabset(data->nb_rooms, 0)))
        return (NULL);
    if (!(queue = ft_tabset(data->nb_rooms, -1)))
        return (NULL);
    queue[0] = 0;
    while (queue[0] != 1 && queue[0] != -1)
    {
        i = 0;
        while (i < (int)data->nb_rooms)
        {
            if (i != queue[0] && tmp_matrix[queue[0]][i] == 1 && tmp_matrix[i][i] == 0) // EV : si la salle en premiere position dans la queue est en lien avec la salle i qu'on passe en revue
            {
                j = 0;
                while (queue[j] != -1)
                    j++;
                queue[j] = i;
                tmp_matrix[i][i] = 1; // on note qu'on a passe la salle i en revue
                if (path[i] == -1)
                path[i] = queue[0];
            }
            else if (i != queue[0] && tmp_matrix[queue[0]][i] == 1 && tmp_matrix[i][i] >= 2 && queue[0] > 0 && data->block[i] != -1) // cas ou bloquage par une room deja empruntée
            {
                path[i] = queue[0];
                data->block[i] = deadlock++;
            }
            i++;
        }
        next_queue(data, queue); //suppression de la room qu'on vient de regarder et on swap pour que queue[0] soit la prochaine room a regarder
    }
    return (path);
}
