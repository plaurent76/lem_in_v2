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

int	 ffy(int **mx, int y, int size_x)
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

	y = ffy(mx, size_y);
	ft_memcpy(mx[y], mx[y_src], (size_x) * sizeof(int));
	return y;
}

void	add_to_path(int **mx, int y, int id)
{
	if (!room_in_path(mx, y, id)) {
		mx[y][ffx(y)] = id;
		return ;
	}
	del_path(mx, y);
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

bool	room_in_path(int **mx, int y, int id)
{
	int 	i;

	i = -1;
	while (mx[y][++i] != -1 && mx[y][++i] != 1)
		if (mx[y][i] == id)
			return true;
	return false;
}

void	path_finder(t_data *data)
{
	int 	**mx;

	int 	y;
	int 	n;
	int 	**links;

	if (!(mx = alloc_matrix_int(data->nb_rooms, data->nb_rooms, -1)))
		return ;
	links = data->matrix;
	n = (int)data->nb_rooms;
	ft_free_matrix(&mx);
	expore_paths(links, mx, NULL, 0);
}

void 	explore_paths(int **links, int **mx, int from, int id)
{
	y = -1;

	if (!from)
	{
		from = ffy(mx);
	}
	while (++y < n)
	{
		if (links[y][id]) // link exists with start
		{
			mx
		}
	}

}
