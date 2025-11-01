/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:18:18 by jpluta            #+#    #+#             */
/*   Updated: 2025/11/01 16:27:41 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*helper(char *path);

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

int	test_if_openable_and_valid(char *path, int *status)
{
	int		fd;
	char	*file_name;

	file_name = helper(path);
	if (!file_name)
		return (0);
	if (*status != 0)
	{
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
