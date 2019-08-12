/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 11:56:05 by eviana            #+#    #+#             */
/*   Updated: 2019/07/30 16:02:25 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "ft_printf.h"
# include <fcntl.h>

typedef struct	s_room
{
	char	*name;
	int		x;
	int		y;
}				t_room;

typedef struct	s_path
{
	int		**paths;
}				t_path;

/*
typedef struct	s_path
{
	char			*path;
	int				flow;
	int				size;
	int				nb_ants;
	struct s_path	*next;
}				t_path;
*/

typedef struct	s_data
{
	int		*score;
	int		*block;
	int		flow_max;
	char	**input;
	int		*line_type;
	t_room	*rooms;

	size_t	nb_rooms;
	size_t	nb_paths;
	int 	nb_valid;
	int		nb_ants;
	int		**matrix;
	int 	**paths;
}				t_data;

void	path_finder(t_data *data);
int		get_path_size(int *path_found);
int		choice_path(t_data *data, t_path *path);
int		*init_res(t_data *data, int *res);
void	print_paths(t_data data, t_path *path);
void	count_flow_max(t_data *data);
int		filling(t_data *data, int line_nb, int room_nb);
int		get_data(t_data *data, char *input);
int		get_type(char *line);
int		alloc_rooms(t_data *data);
int		**alloc_matrix(int x, int y, int id);
char	*get_input(int fd);
int		get_room(t_data *data);
void	print_input(char **input);
void	print_matrix(t_data *data, int **matrix);
void	init(t_data *data);
void	ft_strtabdel(char **str);
void	ft_inttabdel(int **tab);
int		*bfs(t_data *data, int **matrix);
t_path	*ek(t_data *data);
t_path	*newpath(t_path *path_list, t_path *all_paths, int flow);
int		**ft_matrixdup(int **src, size_t size);
void	ft_print_tab(int *tab, size_t size);
int		*ft_tabnew(size_t size);
int		*ft_tabset(size_t size, int init_nb);
void	print_one_path(int *path);

#endif