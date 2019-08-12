/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 12:04:36 by eviana            #+#    #+#             */
/*   Updated: 2019/07/26 01:04:22 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void         count_flow_max(t_data *data)
{
    int     i;
    int     flow_start;
    int     flow_end;

    flow_start = 0;
    flow_end = 0;
    i = 0;
    while (i < (int)data->nb_rooms)
    {
        if (data->matrix[0][i] == 1 && i != 0)
            flow_start++;
        if (data->matrix[1][i] == 1 && i != 1)
            flow_end++;
        i++;
    }
    if (flow_end <= flow_start)
        data->flow_max = flow_end;
    else
        data->flow_max = flow_start;
}

static int		tag_limit(char *line)
{
	if (ft_strequ(line, "##start"))
		return (4);
	if (ft_strequ(line, "##end"))
		return (5);
	return (6);
}

static int		check_type(char **split, int type)
{
	int	i;

	i = 0;
	if (type == 2)
	{
		while (split[0][i])
			if (split[0][i] >= 127 || split[0][i++] < 32)
				return (0);
		while (split[1][i])
			if (split[1][i] < 48 || split[1][i++] > 57)
				return (0);
		while (split[2][i])
			if (split[2][i] < 48 || split[2][i++] > 57)
				return (0);
	}
	if (type == 3)
	{
		while (split[0][i] && split[0][i] != '-')
			if (split[0][i] >= 127 || split[0][i++] < 32)
				return (0);
		if (!split[0][i++])
			return (0);
		while (split[0][i])
			if (split[0][i] >= 127 || split[0][i++] < 32)
				return (0);
	}
	return (1);
}

int		get_type(char *line)//il faut rajouter une verif qu'il y est bien start et end, un nb de fourmie valide etc
{
	int		i;
	int		type;
	char	**split;

	type = 0;
	if (line[0] == '#')
		type = tag_limit(line);
	else if ((split = ft_strsplit(line, ' ')))
	{
		i = 0;
		while (split[i])
			i++;
		if (i == 3)
			type = 2;
		else if (i == 1)
		{
			if (ft_strstr(line, "-"))
				type = 3;
			else
				type = 6;
		}
		else 
			type = 0;
		if (!(check_type(split, type)))
		{
			ft_putnbr(type);
			ft_strtabdel(split);
			return (0);
		}
		ft_strtabdel(split);
	}
	return (type);
}

static int     count_nb_rooms(t_data *data)
{
	int		i;
    int     line_nb;

	i = 0;
    line_nb = 0;
	while (data->input[i])
		i++;
	if (!(data->line_type = (int*)malloc(sizeof(int) * (i))))
		return (0);
    while (data->input[line_nb])
    {
        if (!(data->line_type[line_nb] = get_type(data->input[line_nb])))
		{
			write(0, "wrong type line:", 16);
			ft_putnbr(line_nb);
			break ;
		}
		if (data->line_type[line_nb] == 2)
            data->nb_rooms++;
        line_nb++;
    }
	if (data->line_type[0] != 6)
	{
		write(0, "wrong nb ants\n", 14);
		return (0);
	}
    return (1);
}

void	check_matrix(t_data *data)
{
	int		i;
	int		tmp_i;
	int		j;
	int		tube;

	i = 1;
	tmp_i = 0;
	while (i < (int)data->nb_rooms)
	{
		tube = -1;
		j = 0;
		while (j < (int)data->nb_rooms)
		{
			if (data->matrix[i][j] == 1 && i != j && tube == -1)
				tube = j;
			else if (data->matrix[i][j] == 1 && i != j && tube >= 0)
			{
				tube = -1;
				break ;
			}
			j++;
		}
		if (tube >= 0 && i >= 2)//ces deux conditions font que si on a une impasse on regarde ensuite la room lier a limpasse et ainsi de suite sinon  on avance avec i normalament mais dans le cas ou on avais impasse et que on a mtn plus on repart avec i++ par rapport a la premiere impasse
		{
			data->matrix[tube][i] = 0;
			data->matrix[i][tube] = 0;
			i = tube;
		}
		else
			i = ++tmp_i;
	}
}

int		get_data(t_data *data, char *input)
{
	int		room_nb;
	int		line_nb;

	room_nb = 2;
	line_nb = 0;
	if (!(data->input = ft_strsplit(input, '\n')))
		return (0);
	//ft_strdel(&input);
	if (!count_nb_rooms(data))
		return (0);
	if (!alloc_rooms(data) || (!(data->matrix = alloc_matrix(data->nb_rooms, data->nb_rooms, 0))))
		return (0);
	while (data->input[line_nb])
	{
		if (data->line_type[line_nb] == 0)
			break ;//quand on recois un type non valable on doit essayer avec les lignes d'avant
		else if (!(room_nb = filling(data, line_nb, room_nb)))
			return (0);
		if (data->line_type[line_nb] == 4 || data->line_type[line_nb] == 5)
			line_nb++;
		line_nb++;
	}
	check_matrix(data);
	return (1);
}
