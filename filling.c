#include "lem_in.h"

static int		fill_room(t_data *data, int line_nb, int room_nb)
{
	char **split;

	if (!(split = ft_strsplit(data->input[line_nb], ' ')))
		return (0);
	if (!(data->rooms[room_nb].name = ft_strdup(split[0])))
	{
		ft_strtabdel(split);
		return (0);
	}
	//data->rooms[room_nb].x = ft_atoi(split[1]);
	//data->rooms[room_nb].y = ft_atoi(split[2]); ca fait segf
	ft_strtabdel(split);
	return (1);
}

/*void			ft_swap(int *x, int *y)
{
	int		tmp;

	tmp = *x;
	*y = *x;
	*x = tmp;
}*/

static int		fill_matrix(t_data *data, int line_nb)
{
	int		i;
	int 	x;
	int		y;
	char	**split;

	i = 0;
	x = -1;
	y = -1;
	if (!(split = ft_strsplit(data->input[line_nb], '-')))
		return (0);
	while (i < (int)data->nb_rooms && (x == -1 || y == -1))
	{
		if (ft_strequ(split[0], data->rooms[i].name))
			x = i;
		else if (ft_strequ(split[1], data->rooms[i].name))
			y = i;
		i++;
	}
	if (x >= 0 && y >= 0)
	{
		data->matrix[y][x] = 1;
		//ft_swap(&x, &y);
		data->matrix[x][y] = 1;
	}
	ft_strtabdel(split);
	return (1);
}

int filling(t_data *data, int line_nb, int room_nb)
{
	if (data->line_type[line_nb] == 6)
		data->nb_ants = ft_atoi(data->input[line_nb++]);
	else if (data->line_type[line_nb] == 4)
	{
		if (!(fill_room(data, ++line_nb, 0)))
			return (0);
	}
	else if (data->line_type[line_nb] == 5)
	{
		if (!(fill_room(data, ++line_nb, 1)))
			return (0);
	}
	else if (data->line_type[line_nb] == 2)
	{
		if (!(fill_room(data, line_nb, room_nb++)))
			return (0);
	}
	else
	{
		if (!fill_matrix(data, line_nb))
			return (0);
	}
	return (room_nb);
}