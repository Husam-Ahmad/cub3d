/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:14:46 by jpluta            #+#    #+#             */
/*   Updated: 2025/10/18 17:36:25 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_file_data(char *p_to_file, t_data *data)
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
		process_line_for_valid_check(line, data);
		free(line);
		line = get_next_line(file);
	}
	close(file);
	if (valid_data(data->valid_file_data))
		process_file_data(data, p_to_file);
	else
		return (0);
	return (1);
}

void	process_line_for_valid_check(char *line, t_data *data)
{
	int	i;

	i = 0;
	if (line[0] == '\n')
		return ;
	line = skip_empty_spaces(line);
	if (line[i])
		extract_data(&line[i], data);
	else
		return ;
}

void	extract_data(char *line, t_data *data)
{
	printf("line: %s\n", line);
	if (line && (ft_strncmp(line, "NO", 2) == 0))
	{
		line += 2;
		data->path_to_the_north_texture = skip_empty_spaces(line);
		if (test_if_openable(data->path_to_the_north_texture))
			data->valid_file_data.NO_path_to_the_north_texture = 1;
	}
	else if (line && (ft_strncmp(line, "SO", 2) == 0))
	{
		line += 2;
		data->path_to_the_south_texture = skip_empty_spaces(line);
		if (test_if_openable(data->path_to_the_south_texture))
			data->valid_file_data.SO_path_to_the_south_texture = 1;
	}
	else if (line && (ft_strncmp(line, "WE", 2) == 0))
	{
		line += 2;
		data->path_to_the_west_texture = skip_empty_spaces(line);
		if (test_if_openable(data->path_to_the_west_texture))
			data->valid_file_data.WE_path_to_the_west_texture = 1;
	}
	else
		extract_data_2(line, data);
}

void	extract_data_2(char *line, t_data *data)
{
	if (line && (ft_strncmp(line, "EA", 2) == 0))
	{
		line += 2;
		data->path_to_the_east_texture = skip_empty_spaces(line);
		if (test_if_openable(data->path_to_the_east_texture))
			data->valid_file_data.EA_path_to_the_east_texture = 1;
	}
	else if (line && (ft_strncmp(line, "F", 1) == 0))
		data->valid_file_data.F = 1;
	else if (line && (ft_strncmp(line, "C", 1) == 0))
		data->valid_file_data.C = 1;
	else if (line)
	{
		if (find_map(line) == 1)
			data->valid_file_data.map_rows++;
	}
}
