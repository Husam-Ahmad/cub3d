/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:18:18 by jpluta            #+#    #+#             */
/*   Updated: 2025/10/18 16:13:05 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	valid_data(t_valid_file_data valid_file_data)
{
	if (!valid_file_data.NO_path_to_the_north_texture)
		return (0);
	else if (!valid_file_data.SO_path_to_the_south_texture)
		return (0);
	else if (!valid_file_data.WE_path_to_the_west_texture)
		return (0);
	else if (!valid_file_data.EA_path_to_the_east_texture)
		return (0);
	else if (!valid_file_data.F)
		return (0);
	else if (!valid_file_data.C)
		return (0);
	else if (valid_file_data.map_rows <= 2)
		return (0);
	else
		return (1);
}

int	test_if_openable(char *path)
{
	int	fd;
	// printf("FROM OPENABLE %s\n", path);

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (1); // zmen s5 na '0'
	else
	{
		close(fd);
		return (1);
	}
}

char	*skip_empty_spaces(char *line)
{
	int	i;

	i = 0;
	if (line[i])
	{
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
	}
	return (&line[i]);
}