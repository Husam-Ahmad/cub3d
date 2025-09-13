/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:13:45 by jpluta            #+#    #+#             */
/*   Updated: 2025/09/13 13:57:19 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	close(file);
	return (0);
}

void	process_line_for_parsing(char *line, t_data *data)
{
	int	i;

	i = 0;
	if (line[0] == '\n')
		return ;
	line = skip_empty_spaces(line);
	if (line[i])
		extract_data_parsing(&line[i], data);
	else
		return ;
}

void	extract_data_parsing(char *line, t_data *data)
{
	char *trimmed_line;

	if (line && (ft_strncmp(line, "NO", 2) == 0))
	{
		line += 2;
		trimmed_line = skip_empty_spaces(line);
		data->path_to_the_north_texture = ft_strdup(trimmed_line);
	}
	else if (line && (ft_strncmp(line, "SO", 2) == 0))
	{
		line += 2;
		trimmed_line = skip_empty_spaces(line);
		data->path_to_the_south_texture = ft_strdup(trimmed_line);
	}
	else if (line && (ft_strncmp(line, "WE", 2) == 0))
	{
		line += 2;
		trimmed_line = skip_empty_spaces(line);
		data->path_to_the_west_texture = ft_strdup(trimmed_line);
	}
	else
		extract_data_parsing_2(line, data);
}

void	extract_data_parsing_2(char *line, t_data *data)
{
	char	*trimmed_line;
	
	if (line && (ft_strncmp(line, "EA", 2) == 0))
	{
		line += 2;
		trimmed_line = skip_empty_spaces(line);
		data->path_to_the_east_texture = ft_strdup(trimmed_line);
	}
	else if (line && (ft_strncmp(line, "F", 1) == 0))
	{
		line += 1;
		trimmed_line = skip_empty_spaces(line);
		parse_colours(trimmed_line, &data->F);
	}
	else if (line && (ft_strncmp(line, "C", 1) == 0))
	{
		line += 1;
		trimmed_line = skip_empty_spaces(line);
		parse_colours(trimmed_line, &data->C);
	}
	else if (line && valid_data(data->valid_file_data) == 1)
	{
		if (find_map(line) == 0)
			return ;
		// else
		// 	parse_map(line, data);
	}
}


void	parse_colours(char *line, t_colours *colour)
{
	int	i;

	i = 0;
	if (line[i] && ft_isdigit((int)(line[i])))
		colour->R = ft_atoi(&line[i]);
	while (line[i] && (line[i] >= '0' && line[i] <= '9'))
        i++;
	while (line[i] && (line[i] == ' ' || line[i] == ',' || line[i] == '\t'))
		i++;
	if (line[i] && ft_isdigit((int)(line[i])))
		colour->G = ft_atoi(&line[i]);
	while (line[i] && (line[i] >= '0' && line[i] <= '9'))
        i++;
	while (line[i] && (line[i] == ' ' || line[i] == ','|| line[i] == '\t'))
		i++;
	if (line[i] && ft_isdigit((int)(line[i])))
		colour->B = ft_atoi(&line[i]);
}