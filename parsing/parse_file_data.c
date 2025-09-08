/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:14:46 by jpluta            #+#    #+#             */
/*   Updated: 2025/09/08 19:21:09 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_and_process_file(char *p_to_file, t_data *data)
{
	int		file;
	char	*line;

	file = open(p_to_file, O_RDONLY);
	if (!file)
	{
		perror("Error opening file");
		return (1);
	}
	line = get_next_line(file);
	while (line)
	{
		process_line(line, data);
		line = get_next_line(file);
	}
	close(file);
	return (0);
}

void	process_line(char *line, t_data *data)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n' && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '\n')
		return ;
	if (line[i])
		extract_data(&line[i], data, &i);
	else
		return ;
}

void	extract_data(char *line, t_data *data, int *i)
{
	if (line[*i] && (ft_strncmp(&line[*i], "NO", 2) == 1))
	{
		*i += 2;
		data->path_to_the_north_texture = skip_empty_spaces(&line[*i], i);
		if (test_if_openable(data->path_to_the_north_texture))
			data->valid_file_data.NO_path_to_the_north_texture = 1;
	}
	else if (line[*i] && (ft_strncmp(&line[*i], "SO", 2) == 1))
	{
		*i += 2;
		data->path_to_the_south_texture = skip_empty_spaces(&line[*i], i);
		if (test_if_openable(data->path_to_the_south_texture))
			data->valid_file_data.SO_path_to_the_south_texture = 1;
	}
	else if (line[*i] && (ft_strncmp(&line[*i], "WE", 2) == 1))
	{
		*i += 2;
		data->path_to_the_west_texture = skip_empty_spaces(&line[*i], i);
		if (test_if_openable(data->path_to_the_west_texture))
			data->valid_file_data.WE_path_to_the_west_texture = 1;
	}
	else if (line[*i] && (ft_strncmp(&line[*i], "EA", 2) == 1))
	{
		*i += 2;
		data->path_to_the_east_texture = skip_empty_spaces(&line[*i], i);
		if (test_if_openable(data->path_to_the_east_texture))
			data->valid_file_data.EA_path_to_the_east_texture = 1;
	}
	else if (line[*i] && (ft_strncmp(&line[*i], "F", 1) == 1))
	{
		*i += 1;
		data->path_to_the_east_texture = skip_empty_spaces(&line[*i], i);
	}
	else if (line[*i] && (ft_strncmp(&line[*i], "C", 1) == 1))
	{
		*i += 1;
		data->path_to_the_east_texture = skip_empty_spaces(&line[*i], i);
	}
}

int	test_if_openable(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd != -1)
		return (0);
	else
	{
		close(fd);
		return (1);
	}
}

char	*skip_empty_spaces(char *line, int *i)
{
	if (line[*i])
	{
		while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
			*i++;
	}
	return (&line[*i]);
}
