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

int     ffi(int **mx)
{

}

void    path_finder(t_data *data)
{
    int     **paths;

    int     i;
    if (!(alloc_matrix_int(data->nb_rooms, data->nb_rooms))
        return (NULL);

    ft_free_matrix(&path);
}