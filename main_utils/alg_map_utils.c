/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:14:13 by jpluta            #+#    #+#             */
/*   Updated: 2025/11/09 13:00:52 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_boundaries(t_data *data)
{
	int	rows;
	int	cols;

	rows = data->valid_file_data.map_rows;
	cols = find_longest_line(data->map);
	if (!is_map_enclosed(data->map, rows, cols))
		return (-1);
	return (0);
}

int	find_longest_line(char **map)
{
	int	longest;
	int	i;

	longest = 0;
	i = 0;
	while (map[i])
	{
		if (longest < (int)ft_strlen(map[i]))
			longest = (int)ft_strlen(map[i]);
		i++;
	}
	return (longest);
}
