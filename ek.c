/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ek.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 15:20:25 by plaurent          #+#    #+#             */
/*   Updated: 2019/08/01 17:48:37 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void    open_upstream(t_data *data, int **tmp_matrix, int blocked_room)
{
    int i;
    int j;

    i = blocked_room; 
    j = 0;
    while (j < (int)data->nb_rooms && i > 0)
    {
        if (tmp_matrix[i][j] >= 2 && i != j && tmp_matrix[i][i] <= tmp_matrix[i][j])
        {
            tmp_matrix[i][j] = 1;
            tmp_matrix[j][i] = 1;
            if (tmp_matrix[i][i] >= 2 && i != blocked_room)
                tmp_matrix[i][i] = 0;
            i = j;
            j = 0;
        }
        else
            j++;
    }
}

void    open_downstream(t_data *data, int **tmp_matrix, int blocked_room)
{
    int i;
    int j;

    i = blocked_room; 
    j = 0;
    while (j < (int)data->nb_rooms && i > 0)
    {
        if (tmp_matrix[i][j] >= 2 && i != j && tmp_matrix[i][i] > tmp_matrix[i][j])
        {
            tmp_matrix[i][j] = 1;
            tmp_matrix[j][i] = 1;
            if (tmp_matrix[i][i] >= 2)
                tmp_matrix[i][i] = 0;
            i = j;
            j = 0;
        }
        else
            j++;
    }
}

int     is_shorter(int *first_path, int *new_path)
{
    int i;
    int first_size;
    int new_size;

    i = 1;
    new_size = 0;
    while (i > 0)//on compte la taille de new_path
    {
        if (new_path[i] >= 0)
            i = new_path[i];
        else
            break;
        new_size++;
    }
    i = 1;
    first_size = 0;
    while (i > 0 && first_path[1] != -1)//on compte la taille de first_path
    {
        if (first_path[i] >= 0)
            i = first_path[i];
        else
            break;
        first_size++;
    }
    if (new_size < first_size)//si new_path < first_path
        return (1);
    return (0);
}

/*
update matrix sert a modifier la matrix en fonction de new_path
pour enregistrer le chemins dans la matrix
*/
static void update_matrix(t_data *data, int *new_path)
{
    int     room;
    int     i;

    room = 1;
    i = 0;
    ft_putstr("Update matrix : \n");
    while (room != 0)
    {
        ft_printf("%s|", data->rooms[room].name); // TEST
        data->matrix[room][room] = 2 + i;
        if (new_path[room] >= 0)
        {
            data->matrix[room][new_path[room]] = 2 + i;
            data->matrix[new_path[room]][room] = 2 + i;
            i++;
        }
        room = new_path[room];
    }
    ft_printf("%s\n", data->rooms[room].name); // TEST
    data->matrix[1][1] = 0;
}

/*
char    *sp_join_res(char *all_res, int *res)
{
    char    *str;
    int     j;
    int     i;
    int     size;

    i = 1;
    j = 0;
    size = get_path_size(res);
    if (!(str = malloc(sizeof(char) * size + 1)))
        return (NULL);
    while(i > 0)
    {
        str[j] = i + '0';
        i = res[i];
        j++;
    }
    str[j] = '\n';
    if (!all_res)
        return (str);
    else
        return (all_res = ft_strjoin(all_res, str));
}*/

void    add_paths(t_path *all_paths, int *new_path, int flow)
{
    int i;

    i = 0;
    while (i < flow - 1)
    {
        all_paths[flow].paths[i] = all_paths[flow - 1].paths[i];  
        i++;
    }
    all_paths[flow].paths[flow - 1] = new_path;
}

int     find_other_paths(t_data *data, t_path *all_paths, int flow) // EV : C'est sur qu'il faut reboucler sur check blocking ou faire autrement
{
    int     i;
    int     *new_path;

    i = 0;
    while (i < flow) // en gros si on a blocage et qu'on trouve une soluce il faut trouver le ou les autres chemins qui marchent avec cette alternative
    {                //faudra peut etre rajouter des conditions si le nouveau chemin ne cree pas d'autres blocage et donc peut etre recommencer avec check blocking
                     //et on est sur que ca ne tournera pas en boucle car un blocage ne peut pas etre tester 2x mais a faire attention que ce ne soit pas trop long comme ce commentaire
        if (!(new_path = bfs(data, data->matrix)))
            return (0);
        if (new_path[1] != -1)
        {
            ft_putstr("New path in find other path : \n");
            print_one_path(new_path);
            update_matrix(data, new_path);
            all_paths[flow].paths[i + 1] = new_path; // EV : On ajoute un chemin, i + 1 car la case [0] est prise depuis la fonction blocking 
            //all_res = sp_join_res(all_res, new_path);
            //path = newpath(path, new_path, flow); //a verif si il ya un cas ou en deblocant on trouve une alternative au premier chemin mais qu'on trouve tjrs pas de deuxieme chemins
        }
        else //EV : ici pour le rebouclage check blocking ?
            return (0);
        i++;
    }
    return (1);
}

int     *check_blocking(t_data *data, int *first_path)
{
    int i;
    int *new_path;
    int **tmp_matrix;

    while (1) // tant que tout les blocages n'ont pas ete traités
    {
        tmp_matrix = ft_matrixdup(data->matrix, data->nb_rooms);
        i = 0;
        while (i < (int)data->nb_rooms && data->block[i] <= 0) //on cherche un blocage et si il n'y en a pas on sort de check blocking
            i++;
        if (i == (int)data->nb_rooms) // EV : useless ?
            return (first_path);
        open_upstream(data, tmp_matrix, i);
        if (!(new_path = bfs(data, tmp_matrix))) //teste en ayant debloquer
            return (NULL);
        if (new_path[1] != -1)//TEST
        {
            ft_putstr("New path in check_blocking : \n");//TEST
            print_one_path(new_path);//TEST
        }
        if ((new_path[1] != -1 && is_shorter(first_path, new_path)) || (first_path[1] == -1 && new_path[1] != -1)) // soit le nouveau chemin est plus rapide
        {
            open_downstream(data, tmp_matrix, i);
            data->matrix = tmp_matrix;
            first_path = new_path;
        }
        data->block[i] = -1; //supprime blocage et le met en "deja check" d'ou le -1
    }
    return (first_path); // EV : et pas return (new_path); ???
}

int     blocking(t_data *data, int *first_path, t_path *all_paths, int flow)
{//important, dans check blocking si on a trouver des nouveau chemins mais avant il y avait eu d'autre chemins il faut peut etre comparer leur deux score ou alors c est inutile ?
    //char    *tmp_all_res = NULL;
    int     *new_path;

    new_path = check_blocking(data, first_path);
    if (new_path[1] != -1)
    {
        ft_putstr("New path in blocking : \n");
        print_one_path(new_path);
        //tmp_all_res = sp_join_res(tmp_all_res, new_path); // STOP DEV ACTUEL
        update_matrix(data, new_path);
        all_paths[flow].paths[0] = new_path; // EV : On ajoute un chemin // Faire peut etre une fonction pour mettre a la premiere place dispo

        if (new_path == first_path) // EV : voir ca dans check_blocking // Pas sur // a mettre au debut de la fonction ?
            add_paths(all_paths, new_path, flow); //Pas sur
        else if (find_other_paths(data, all_paths, flow))
            return (1);
        return (1);
        //else
        //    return (all_path);
    }
    else
        printf("CHECK BLOCKING N'A TROUVE AUCUNE SOLUTION !!!\n");//TEST
    return (0);
}

t_path     *init_all_paths(int flow_max) // Rajouter une initialisation a NULL ?
{
    t_path *all_paths;
    int         i;

    i = 1;
    if (!(all_paths = (t_path*)malloc(sizeof(t_path) * flow_max + 1)))
        return (NULL);
    while (i <= flow_max)
    {
        if (!(all_paths[i].paths = (int**)malloc(sizeof(int*) * i)))
            return (NULL);
        i++;
    }
    return (all_paths);
}

t_path        *ek(t_data *data)  // RES EST MTN NEW_PATH
{
    int         flow;
    int         *new_path;
    size_t      i;
    t_path      *all_paths;

    flow = 1;
    if (!(all_paths = init_all_paths(data->flow_max)))
        return (NULL);
    while (flow <= data->flow_max)
    {
        if (!(new_path = bfs(data, data->matrix)))
            return (all_paths);
        i = 0;
        while (i < data->nb_rooms && data->block[i] <= 0)//on cherche un blocage
            i++;
        if (new_path[1] >= 0 && i == data->nb_rooms)//cas de non blocage
        {
            ft_printf("EK : Cas de chemin libre pour flow(%d)\n", flow);//TEST
            update_matrix(data, new_path);
            add_paths(all_paths, new_path, flow);
        }
        else//cas de blocage
        {
            ft_printf("EK : Cas de blocage pour flow(%d)\n", flow);//TEST
            ft_putstr("New path before blocking : \n");//TEST
            print_one_path(new_path);//TEST
            if (!blocking(data, new_path, all_paths, flow))// flow a ete modifie (+1)
                return (NULL);
        }
        flow++;
    }
    //data->flow_max = flow - 1;
    return (all_paths);
}
