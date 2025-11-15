/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:13:45 by jpluta            #+#    #+#             */
/*   Updated: 2025/11/15 13:31:34 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	extract_data_parsing_3(char *line, t_data *data, char *map_line);

int	process_file_data(t_data *data, char *p_to_file)
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
		process_line_for_parsing(line, data);
		free(line);
		line = get_next_line(file);
	}
	data->map[data->valid_file_data.map_rows] = NULL;
	close(file);
	if (check_boundaries(data) == -1)
	{
		return (-1);
	}
	return (0);
}

void	process_line_for_parsing(char *line, t_data *data)
{
	int		i;
	char	*map_line;

	map_line = line;
	i = 0;
	if (line[0] == '\n')
		return ;
	line = skip_empty_spaces(line);
	if (line[i])
		extract_data_parsing(&line[i], data, map_line);
	else
		return ;
}

void	extract_data_parsing(char *line, t_data *data, char *map_line)
{
	char	*trimmed_line;

	if (line && (ft_strncmp(line, "NO", 2) == 0))
	{
		line += 2;
		trimmed_line = skip_empty_spaces(line);
		data->path_to_the_north_texture = helper(trimmed_line);
	}
	else if (line && (ft_strncmp(line, "SO", 2) == 0))
	{
		line += 2;
		trimmed_line = skip_empty_spaces(line);
		data->path_to_the_south_texture = helper(trimmed_line);
	}
	else if (line && (ft_strncmp(line, "WE", 2) == 0))
	{
		line += 2;
		trimmed_line = skip_empty_spaces(line);
		data->path_to_the_west_texture = helper(trimmed_line);
	}
	else
		extract_data_parsing_2(line, data, map_line);
}

void	extract_data_parsing_2(char *line, t_data *data, char *map_line)
{
	char	*trimmed_line;

	if (line && (ft_strncmp(line, "EA", 2) == 0))
	{
		line += 2;
		trimmed_line = skip_empty_spaces(line);
		data->path_to_the_east_texture = helper(trimmed_line);
	}
	else if (line && (ft_strncmp(line, "F", 1) == 0))
	{
		line += 1;
		trimmed_line = skip_empty_spaces(line);
		parse_colours(trimmed_line, &data->f);
	}
	else if (line && (ft_strncmp(line, "C", 1) == 0))
	{
		line += 1;
		trimmed_line = skip_empty_spaces(line);
		parse_colours(trimmed_line, &data->c);
	}
	else if (line)
		parse_map(map_line, data);
}
