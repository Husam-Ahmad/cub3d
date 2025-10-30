/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:18:18 by jpluta            #+#    #+#             */
/*   Updated: 2025/10/30 18:46:06 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	valid_data(t_valid_file_data valid_file_data)
{
	// printf("%d\n", valid_file_data.NO_path_to_the_north_texture);
	// printf("%d\n", valid_file_data.SO_path_to_the_south_texture);
	// printf("%d\n", valid_file_data.WE_path_to_the_west_texture);
	// printf("%d\n", valid_file_data.EA_path_to_the_east_texture);
	// printf("%d\n", valid_file_data.F);
	// printf("%d\n", valid_file_data.C);
	// printf("%d\n", valid_file_data.map_rows);



	
	// if (!valid_file_data.NO_path_to_the_north_texture)
	// 	return (0);
	// else if (!valid_file_data.SO_path_to_the_south_texture)
	// 	return (0);
	// else if (!valid_file_data.WE_path_to_the_west_texture)
	// 	return (0);
	// else if (!valid_file_data.EA_path_to_the_east_texture)
	// 	return (0);
	/*else */if (!valid_file_data.F)
		return (0);
	else if (!valid_file_data.C)
		return (0);
	else if (valid_file_data.map_rows <= 2)
		return (0);
	else
		return (1);
}

int	test_if_openable_and_valid(char *path, int *status)
{
	int	fd;

	printf("%s\n", path);
	if (*status != 0)
	{
		*status = -1;
		return (0);
	}
	fd = open(path, O_RDONLY);
	if (fd != -1)
	{
		close(fd);
		return (1);
	}
	else if (fd == -1)
	{
        perror("open");
		return (0);
	}
	else
		return (0);
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
