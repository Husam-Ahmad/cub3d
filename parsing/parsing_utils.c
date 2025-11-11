/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:18:18 by jpluta            #+#    #+#             */
/*   Updated: 2025/11/11 17:05:18 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	valid_data(t_valid_file_data valid_file_data)
{
	if (valid_file_data.no_path_to_the_north_texture != 1)
		return (0);
	else if (valid_file_data.so_path_to_the_south_texture != 1)
		return (0);
	else if (valid_file_data.we_path_to_the_west_texture != 1)
		return (0);
	else if (valid_file_data.ea_path_to_the_east_texture != 1)
		return (0);
	else if (valid_file_data.c != 1)
		return (0);
	else if (valid_file_data.f != 1)
		return (0);
	else if (valid_file_data.map_rows <= 2)
		return (0);
	else
		return (1);
}

int	test_if_openable_and_valid(char *path, int *status)
{
	int		fd;
	char	*file_name;

	file_name = helper(path);
	if (!file_name)
		return (0);
	if (*status != 0)
	{
		free(file_name); // we added this
		*status = -1;
		return (0);
	}
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		free(file_name);
		perror("open failed");
		return (0);
	}
	else
	{
		free(file_name);
		close(fd);
		return (1);
	}
	return (0);
}

char	*helper(char *path)
{
	char	*file_name;
	int		length;

	file_name = ft_strdup(path);
	if (!file_name)
		return (NULL);
	length = ft_strlen(file_name);
	file_name[length - 1] = '\0';
	return (file_name);
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
