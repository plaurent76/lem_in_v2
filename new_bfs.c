#include "lem_in.h"

void	ft_free_matrix(int ***tab)
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

int	 ffy(int **mx, int size_y)
{
	int i = -1;

	while (++i < size_y) {
		if (mx[i][1] == -1) {
			return i;
		}
	}
	return 0;
}

int	 ffx(int **mx, int y, int size_x)
{
	int i = -1;

	while (++i < size_x) {
		if (mx[y][i] == -1) {
			return i;
		}
	}
	return 0;
}

// duplicates given path row and returns index of duplicated row
int		duplicate_path(int **mx, int size_x, int size_y, int y_src)
{
	int 	y;
	int		i;

	y = ffy(mx, size_y);
	ft_memcpy(mx[y], mx[y_src], (size_x) * sizeof(int));
	i = 0;
	while (mx[y][i] != -1)
		i++;
	mx[y][i - 1] = -1;
	return (y);
}


int		room_in_path(int **mx, int y, int id)
{
	int 	i;

	i = -1;
	while (mx[y][++i] != -1 && mx[y][++i] != 1)
		if (mx[y][i] == id)
			return (1);
	return (0);
}

void	del_path(int **mx, int y)
{
	int 	i;

	i = -1;
	while (mx[y][++i] > -1)
	{
		mx[y][i] = -1;
	}
}

void	add_to_path(int **mx, int size_y, int y, int id)
{
	mx[y][ffx(mx, y, size_y)] = id;
}


void 	explore_paths(int **links, int **mx, int size_y, int path_n, int id)
{
	int 	n_link;
	int 	path_n_duplicate;
	int		x;

	x = -1;
	n_link = 0;
	if (!path_n && mx[0][0] == -1)
	{
		path_n = ffy(mx, size_y);
		add_to_path(mx, size_y, path_n, id);
	}
	path_n_duplicate = path_n;
	while (++x < size_y)
	{
		if (links[id][x] && !room_in_path(mx, x, id)) // link exists with start
		{
			n_link++;
			if (n_link > 1)
			{
				path_n_duplicate = duplicate_path(mx, size_y, size_y, path_n);
			}
			add_to_path(mx, size_y, path_n_duplicate, x);
			explore_paths(links, mx, size_y, path_n_duplicate, x);
		}
	}
	if (n_link == 0)
	{
		del_path(mx, path_n);
	}
}

void	path_finder(t_data *data)
{
	int 	**mx;
	int 	**links;
	int 	n;

	if (!(mx = alloc_matrix(data->nb_rooms, data->nb_rooms, -1)))
		return ;
	links = data->matrix;
	n = (int)data->nb_rooms;
	print_matrix(data, links);
	explore_paths(links, mx, n, 0, 0);
	ft_putstr("teste8");
	print_matrix(data, mx);
		ft_free_matrix(&mx);
}
