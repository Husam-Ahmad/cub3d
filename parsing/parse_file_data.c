/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:14:46 by jpluta            #+#    #+#             */
/*   Updated: 2025/09/08 16:55:19 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_and_process_file(char *p_to_file, t_data *data)
{
	int	*file;
	char	*line;

	file = open(p_to_file, "r");
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
	fclose(file);
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
		data->path_to_the_north_texture = ft_strdup(skip_empty_spaces(&line[*i],
					i));
	}
	else if (line[*i] && (ft_strncmp(&line[*i], "SO", 2) == 1))
	{
		*i += 2;
		data->path_to_the_south_texture = skip_empty_spaces(&line[*i], i);
	}
	else if (line[*i] && (ft_strncmp(&line[*i], "WE", 2) == 1))
	{
		*i += 2;
		data->path_to_the_west_texture = skip_empty_spaces(&line[*i], i);
	}
	else if (line[*i] && (ft_strncmp(&line[*i], "EA", 2) == 1))
	{
		*i += 2;
		data->path_to_the_east_texture = skip_empty_spaces(&line[*i], i);
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

char	*skip_empty_spaces(char *line, int *i)
{
	if (line[*i])
	{
		while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
			*i++;
	}
	return (&line[*i]);
}
