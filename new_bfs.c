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
int		duplicate_path_until(int **mx, int until, int size_y, int y_src)
{
	int 	y;

	y = ffy(mx, size_y);
	ft_memcpy(mx[y], mx[y_src], (until) * sizeof(int));
	return (y);
}

void 	print_path(int *path, int n)
{
	int i = -1;

	while (++i < n)
		(i == (n-1)) ? ft_printf("%d\n", path[i]) : ft_printf(" %d\t| ", path[i]);
}

void 	print_tab(int **tab, int x, int y)
{
	int i = -1;

	while (++i < y)
		print_path(tab[i], x);
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

	length = -1;
	while (mx[path_n][++length] != -1)
	{
		if (mx[path_n][length] == id)
		{
			ft_printf("room %d found in path %d at length %d: ", id, path_n, length);
			print_path(mx[path_n], length + 1);
			return (1);
		}
	}
	ft_printf("room %d NOT found in path %d of length %d: ", id, path_n, length);
	print_path(mx[path_n], length);
	if (path_n > 0) {
		//ft_printf("path_n: %d length: %d\n", path_n, length);
		if (paths_match(mx[path_n], mx[path_n - 1], length)
			&& (id == mx[path_n - 1][length])) {
			return (1);
		}
		//bullshit
		ft_printf("comparing previous path:\n");
		print_path(mx[path_n-1], length);
		ft_printf("with new path:\n");
		print_path(mx[path_n], length);
		ft_printf("path_match:%s\n", paths_match(mx[path_n], mx[path_n - 1], length) ? "yes\n" : "no\n");

		ft_printf("comparing last room of previous with new room to add:\n");
		ft_printf("%d vs %d match:%s\n", id, mx[path_n - 1][length], (id == mx[path_n - 1][length]) ? "yes\n" : "no\n");
		//end of bullshit

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
	int		path_n_length;
	int		x;

	x = -1;
	n_link = 0;

	if (!path_n && mx[0][0] == -1)
	{
		path_n = ffy(mx, size_y);
		add_to_path(mx, size_y, path_n, id);
	}
	path_n_duplicate = path_n;
	path_n_length = 0;
	while (mx[path_n][path_n_length] != -1)
		path_n_length++;
	while (++x < size_y)
	{
		// checks if room is already in path and if path is not duplicate from last one
		if (links[id][x] && !room_used(mx, path_n, x)) // link exists with start
		{
			if (id == 0)
				ft_printf("%d\n", x);
			//ft_printf("%d-%d\n", id, x);
			ft_printf("n_link: %d\n", ++n_link);
			if (n_link > 1)
				path_n_duplicate = duplicate_path_until(mx, path_n_length, size_y, path_n);
			add_to_path(mx, size_y, path_n_duplicate, x);
			print_matrix(data, mx);
			ft_printf("explore path %d from room %d\n", path_n, x);
			if (x != 1)
				explore_paths(data, links, mx, size_y, path_n_duplicate, x);
			else
				data->n_valid++;
		}
	}
	if (n_link == 0)
	{
		// del_path(mx, path_n);
		ft_printf("path %d deleted cause no link\n", path_n);
	}
}

// first valid from
int 	fvf(int **mx, int from, int size_x, int size_y)
{
	int i;
	int j;

	j = from;
	while (j++ < size_y)
	{
		i = -1;
		while (++i < size_x)
			if (mx[j][i] == 1)
				return j;
	}
	return -1;
}

// duplicates given path row and returns index of duplicated row
int		duplicate_path_to_dest(int **mx_src, int y_src, int **mx_dest, int y_dest, int until)
{
	ft_memcpy(mx_dest[y_dest], mx_src[y_src], (until) * sizeof(int));
	return (y_dest);
}

// allocate dynamically data->paths
int 	load_valid_paths(t_data *data, int **mx)
{
	int 	i;
	int 	valid;
	int 	previous_valid;

	if (!(data->paths = alloc_matrix(data->nb_rooms, data->n_valid, -1)))
		return 0;
	i = -1;
	previous_valid = 0;
	while (++i < data->n_valid)
	{
		valid = fvf(mx, previous_valid, data->nb_rooms, data->nb_rooms);
		if (valid == -1)
			return 0;
		duplicate_path_to_dest(mx, valid, data->paths, i, data->nb_rooms);
		previous_valid = valid;
	}
	return 1;
}

void	path_finder(t_data *data)
{
	int 	**mx;
	int 	**links;

	if (!(mx = alloc_matrix(data->nb_rooms, data->nb_rooms, -1)))
		return ;
	links = data->matrix;
	print_matrix(data, links);
	data->n_valid = -1;
	explore_paths(data, links, mx, (int)data->nb_rooms, 0, 0);
	if (!load_valid_paths(data, mx))
		ft_printf("error loading valid paths into data->paths");
	ft_printf("found %d valid paths:\n", data->n_valid);
	print_tab(data->paths, data->nb_rooms, data->n_valid);
	exit(0);
		//ft_free_matrix(&mx);
}
