/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 11:44:53 by eviana            #+#    #+#             */
/*   Updated: 2019/07/24 15:31:15 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char	*sp_strjoinfree(char const *s1, char const *s2) // A METTRE DANS LIBFT
{
	char	*str;
	size_t	size_s1;

	size_s1 = ft_strlen(s1);
	if (!s1 || !s2 || !(str = ft_strnew(size_s1 + ft_strlen(s2) + 1)))
		return (NULL);
	str = ft_strcpy(str, s1);
	str[size_s1] = '\n';
	str[size_s1 + 1] = '\0';
	free((void*)s1); // FT_STRDEL A LA PLACE DE FREE
	return (ft_strcat(str, s2));
}

char         *get_input(int fd)
{
    char    *input;
    char    *line;
    int     lines_read;

    //lines_read = 0;
	input = NULL;
	while ((lines_read = get_next_line(fd, &line, 0)) != -1)
	{
		if (lines_read == 0)
		{
			//ft_strdel(&line);
			return (input);
		}
		else if (!input)
			input = line;
		else
			input = sp_strjoinfree(input, line);
		//ft_strdel(&line); // ft_strdel ?
	}
	return (input); // GESTION ERREUR ?
}
