/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 11:44:53 by eviana            #+#    #+#             */
/*   Updated: 2019/08/01 17:12:19 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			main(int ac, char **av)
{
	int		fd;
	char 	*input;
	t_data	data;
	//t_path	*path;

	if (ac != 2 || (fd = open(av[1], O_RDONLY)) == -1)
		return (0);
	init(&data);
	if (!(input = get_input(fd)))
	{
		close(fd);
		return (0);
	}
	close(fd);
	if (!get_data(&data, input))
		return (0);
	ft_printf("INPUT : \n");// TEST
	print_input(data.input);
	
	count_flow_max(&data);
	print_matrix(&data, data.matrix);
	ft_printf("-------------EK------------\n");
	path_finder(&data);
	//path = ek(&data);
	//ft_printf("CHOICE PATH : \n");
	//choice_path(&data, path);// A REFAIRE AVEC LES NOUVELLES DONNEES

	//ft_printf("\nPATHS for flow max : %d \n", data.flow_max);// TEST
	//print_paths(data, path); // impression temporaire pour verif les resultats
	//print_final(data, path);
	
	return (0);
}
