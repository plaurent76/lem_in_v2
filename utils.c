/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 15:36:27 by eviana            #+#    #+#             */
/*   Updated: 2019/08/01 16:19:13 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int     *init_res(t_data *data, int *res)
{
    size_t  i;

    i = 0;
    if (!res && !(res = malloc(sizeof(int) * data->nb_rooms)))
    		return (NULL);
    while (i < data->nb_rooms)
            res[i++] = -1;
    return (res);
}

int		*ft_tabset(size_t size, int init_nb)
{
	int		*tab;
	size_t	i;

    i = 0;
    if (!(tab = malloc(sizeof(int) * size)))
    		return (NULL);
	while (i < size)
	{
		tab[i] = init_nb;
		i++;
	}
	return (tab);
}

void	ft_print_tab(int *tab, size_t size) // A rajouter dans libft si bien faite
{
	size_t i;

	i = 0;
	while (i < size)
	{
		ft_putnbr(tab[i]);
		i++;
	}
}

int		*ft_tabnew(size_t size)
{
	int		*tab;

	if (!(tab = (int*)malloc(sizeof(int) * size)))
		return (NULL);
	return (tab);
}

int     **ft_matrixdup(int **src, size_t size) // A rajouter dans libft si bien faite
{
	int		**matrix;
	int     i;
    int     j;

    i = 0;
    if (!(matrix = (int**)malloc(sizeof(int*) * size)))
        return (NULL);
    while (i < (int)size)
    {
        j = 0;
        if (!(matrix[i] = (int*)malloc(sizeof(int) * size)))
            return (NULL);
        while (j < (int)size)
        {
            matrix[i][j] = src[i][j];
            j++;
        }
        i++;
    }
    return (matrix);
}

void	init(t_data *data)
{
	data->paths = NULL;
	data->n_valid = -1;
	data->flow_max = 0;
	data->input = NULL;
	data->nb_rooms = 0;
	data->matrix = NULL;
	data->block = NULL;
}

void        print_input(char **input)
{
    int i;
    
    i = 0;
	while (input[i])
	{
		ft_putstr(input[i++]);
		ft_putchar('\n');
	}
}

void		print_one_path(int *path)
{
	int current;

	current = 1;
	ft_putnbr(current);
	ft_putchar('|');
	while (current != 0)
	{
		ft_putnbr(path[current]);
		ft_putchar('|');
		current = path[current];
	}
	ft_putchar('\n');
}

void		print_paths(t_data data, t_path *all_paths)
{
	int flow;
	int i;
	int current;

	flow = 1;
	while (flow <= data.flow_max)
	{
		ft_printf("||flow %d||\n", flow);
		i = 0;
		while (i < flow)
		{
			current = 1;
			ft_putnbr(current);
			ft_putchar('|');
			while (current != 0)
			{
				//ft_printf("print pour flow(%d), i(%d), current(%d)\n", flow, i, current);
				ft_putnbr(all_paths[flow].paths[i][current]);
				write(1, "|", 1);
				current = all_paths[flow].paths[i][current];
			}
			write(1, "\n", 1);
			i++;
		}
		write(1, "\n", 1);
		flow++;
	}
}

/*void		print_final(t_data data, t_path *path)
{
	int		i;
	int		j;

	ft_putnbr(data.flow_max);
	while (path->flow < data.flow_max)
		path = path->next;
	data.matrix[0][0] = data.nb_ants;
	i = 0;
	while (++i < data.nb_rooms)
		data.matrix[i][i] = 0;
	while (data.matrix[1][1] < data.nb_ants) //chaque boucle = une ligne
	{
		i = 0;
		while (i < data.flow_max) // chaque boucle = une fourmie qui se deplace
		{
			j = 0;
			if (data.matrix[j][j] > 0 && )
		}
	}
}*/

void		print_matrix(t_data *data, int **matrix)
{
	int		k;
	int		i;
	int		j;
	int		size[data->nb_rooms];
	int		big_size;

	i = 0;
	big_size = 0;
	while (i < (int)data->nb_rooms)
	{
		if ((size[i] = ft_strlen(data->rooms[i].name)) > big_size)
			big_size = size[i];
		i++;
	}
	i = 0;
	while (i++ < big_size)
		ft_putchar('#');
	ft_putchar('|');
	i = 0;
	while (i < (int)data->nb_rooms)
	{
		ft_putstr(data->rooms[i++].name);
		ft_putchar('|');
	}
	ft_putchar('\n');
	i = 0;
	while ((unsigned long)i++ < ((int)data->nb_rooms + big_size * 2 + data->nb_rooms))
		ft_putchar('-');
	ft_putchar('\n');
	i = -1;
	while (++i < (int)data->nb_rooms)
	{
		j = 0;
		k = size[i];
		ft_putstr(data->rooms[i].name);
		while (k++ < big_size)
			ft_putchar(' ');
		ft_putchar('|');
		while (j < (int)data->nb_rooms)
		{
			k = 1;
			ft_putnbr(matrix[i][j]);
			//if (j == i + 1)
			while (k++ < size[j])
				ft_putchar(' ');
			ft_putchar('|');
			j++;
		}
		ft_putchar('\n');
	}	
}