/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 13:27:46 by jpluta            #+#    #+#             */
/*   Updated: 2025/11/01 16:38:36 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	find_last_lane(char **map);

int	find_map(char *line)
{
	while (*line && *line != '0' && *line != '1')
		line++;
	if (*line == '0' || *line == '1')
		return (1);
	else
		return (0);
}

void	parse_map(char *line, t_data *data)
{
	char	*temp;

	if (data->map == NULL)
	{
		data->map = (char **)malloc((data->valid_file_data.map_rows + 1)
				* sizeof(char *));
		if (!data->map)
			exit(1);
		ft_bzero(data->map, (data->valid_file_data.map_rows + 1)
			* sizeof(char *));
	}
	temp = ft_strdup(line);
	if (!temp)
		exit(1);
	data->map[find_last_lane(data->map)] = temp;
}

int	find_last_lane(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
		i++;
	return (i);
}
