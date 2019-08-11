/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 00:55:48 by eviana            #+#    #+#             */
/*   Updated: 2019/07/26 01:30:24 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
int         get_path_size(int *path_found)// pas une fonction classique
{
    int room_nb;
    int size;

    room_nb = 1;
    size = 0;
    while (room_nb > 0)
    {
        room_nb = path_found[room_nb];
        size++;
    }
    return (size);
}

static t_path *st_create_path(char *path_found, int flow)
{
    t_path *new_path;
    int     size;

    size = ft_strlen(path_found);
    ft_printf("\nSIZE PATH FOUND : %d\n", size); // TEST
    if (!(new_path = (t_path *)malloc(sizeof(t_path))))
        return (NULL);
    //new_path->path = ft_tabcpy(path_found, size);
    // CI DESSOUS ROLE DE TABCPY MAIS NE MARCHE PAS AVEC PATH_FOUND A TROU
    if (!(new_path->path = (char*)malloc(sizeof(t_path) * size)))// +1 pour rajouter la room start
	{
        free(new_path);
        return (NULL);
	}
    ft_strcpy(new_path->path, path_found);
    ft_putstr("\nNEW PATH : ");//TEST
    ft_putstr(new_path->path); //TEST
    ft_putchar('\n');//TEST
    new_path->path = ft_strrev(new_path->path); // TABREV A REVOIR
    ft_putstr("\nNEW PATH REV : ");//TEST
    ft_putstr(new_path->path); //TEST
    ft_putchar('\n');//TESt
    new_path->size = size;
	new_path->flow = flow + 1;
    new_path->nb_ants = 0;
	new_path->next = NULL;
	return (new_path);
}

t_path			*newpath(t_path *path_list, t_all_paths *path_found, int flow)
{
	t_path	*new_path;
	t_path	*temp_path;

	if (!(new_path = st_create_path(path_found, flow)))
	{
		//ft_dellist(&path_list);
		return (NULL);
	}
	if (path_list == NULL)
		return (new_path);
	else
	{
		temp_path = path_list;
		while (temp_path->next != NULL)
			temp_path = temp_path->next;
		temp_path->next = new_path;
		return (path_list);
	}
}*/
