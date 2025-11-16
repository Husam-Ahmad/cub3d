/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:14:13 by jpluta            #+#    #+#             */
/*   Updated: 2025/11/16 12:49:33 by huahmad          ###   ########.fr       */
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

void	set_values(t_rows_cols *rows_and_cols, int rows, int cols, int row)
{
	rows_and_cols->rows = rows;
	rows_and_cols->cols = cols;
	rows_and_cols->row = row;
}

int	must_have_all_data_before_map(t_valid_file_data valid_file_data)
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
	else
		return (1);
}

bool	flood_fill(char **map, bool **visited, t_rows_cols *rows_and_cols,
		int col)
{
	char c;
	int current_row_len;
	bool left;

	if (rows_and_cols->row < 0 || rows_and_cols->row >= rows_and_cols->rows)
		return (false);
	current_row_len = ft_strlen(map[rows_and_cols->row]);
	if (col < 0 || col >= current_row_len)
		return (false);
	if (map[rows_and_cols->row][col] == '1')
		return (true);
	if (visited[rows_and_cols->row][col])
		return (true);
	c = map[rows_and_cols->row][col];
	if (c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != ' ')
		return (false);
	visited[rows_and_cols->row][col] = true;
	rows_and_cols->row -= 1;
	flood_fill(map, visited, rows_and_cols, col);
	rows_and_cols->row += 2;
	flood_fill(map, visited, rows_and_cols, col);
	rows_and_cols->row -= 1;
	left = flood_fill(map, visited, rows_and_cols, col - 1);
	flood_fill(map, visited, rows_and_cols, col + 1);
	return (true);
}
