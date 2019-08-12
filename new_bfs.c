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

void 	print_path(int *path, int n)
{
	int i = -1;

	while (++i < n)
		(i == (n-1)) ? ft_printf("%d\n", path[i]) : ft_printf("%d | ", path[i]);
}

int 	paths_match(int *path1, int *path2, int length)
{
	int 	i;

	i = -1;
	while (++i < length)
		if (path1[i] != path2[i])
			return (0);
	return (1);
}

// checks if room is already in path and if path is not duplicate from last one
int		room_used(int **mx, int path_n, int id)
{
	int 	length;

	length = 0;
	while (mx[path_n][length] != -1)
		if (mx[path_n][length++] == id)
			return (1);
	if (path_n > 0) {
		ft_printf("path_n: %d length: %d\n", path_n, length);
		if (paths_match(mx[path_n], mx[path_n - 1], length - 1)
			&& (id == mx[path_n - 1][length])) {
			return (1);
		}
		// bullshit
		ft_printf("comparing previous path:\n");
		print_path(mx[path_n-1], length);
		ft_printf("with new path:\n");
		print_path(mx[path_n], length);
		ft_printf("path_match:%s\n", paths_match(mx[path_n], mx[path_n - 1], length - 1) ? "yes\n" : "no\n");

		ft_printf("comparing last room of previous with new room to add:\n");
		ft_printf("%d vs %d match:%s\n", id, mx[path_n - 1][length], (id == mx[path_n - 1][length]) ? "yes\n" : "no\n");
		// end of bullshit

	}
	
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


void 	explore_paths(t_data *data, int **links, int **mx, int size_y, int path_n, int id)
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

// checks if room is already in path and if path is not duplicate from last one

		if (links[id][x] && !room_used(mx, path_n, x)) // link exists with start
		{
			ft_printf("%d-%d\n", id, x);
			print_matrix(data, mx);
			n_link++;
			if (n_link > 1)
			{
				path_n_duplicate = duplicate_path(mx, size_y, size_y, path_n);
			}
			add_to_path(mx, size_y, path_n_duplicate, x);
			ft_printf("explore path %d from room %d\n", path_n, x);
			if (x != 1)
				explore_paths(data, links, mx, size_y, path_n_duplicate, x);
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
	explore_paths(data, links, mx, n, 0, 0);
	ft_putstr("teste8");
	print_matrix(data, mx);
	exit(0);
		//ft_free_matrix(&mx);
}
