/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_map_boundaries.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:51:22 by jpluta            #+#    #+#             */
/*   Updated: 2025/10/18 17:34:59 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_boundaries(t_data *data)
{
	int rows = data->valid_file_data.map_rows;
	int cols = find_longest_line(data->map);

	if (!is_map_enclosed(data->map, rows, cols))
		return (-1);

	return (0);
}

int	find_longest_line(char **map)
{
	int longest;
	int i;

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

bool flood_fill(char **map, bool **visited, int rows, int cols, int row, int col)
{
	bool	up;
	bool	down;
	bool	left;
	bool	right;
	char	c;
	
	if (row < 0 || row >= rows || col < 0 || col >= cols)
		return (false);
	if (map[row][col] == '1')
		return (true);
	if (visited[row][col])
		return (true);
	c = map[row][col];
	if (c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != ' ')
		return (false);
	visited[row][col] = (true);
	up = flood_fill(map, visited, rows, cols, row - 1, col);
	down = flood_fill(map, visited, rows, cols, row + 1, col);
	left = flood_fill(map, visited, rows, cols, row, col - 1);
	right = flood_fill(map, visited, rows, cols, row, col + 1);
	return (up && down && left && right);
}

bool is_map_enclosed(char **map, int rows, int cols)
{
	char	c;
	int		start_row;
	int		start_col;
	bool	result;
	bool	**visited;

	start_row = -1;
	start_col = -1;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < (int)ft_strlen(map[i]); j++)
		{
			c = map[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				start_row = i;
				start_col = j;
				break ;
			}
		}
		if (start_row != -1)
			break ;
	}
	if (start_row == -1)
	{
		printf("Error: No player start position found.\n");
		return (false);
	}
	visited = malloc(sizeof(bool *) * rows);
	for (int i = 0; i < rows; i++)
		visited[i] = calloc(cols, sizeof(bool));
	result = flood_fill(map, visited, rows, cols, start_row, start_col);
	for (int i = 0; i < rows; i++)
		free(visited[i]);
	free(visited);
	if (!result)
		printf("Map is NOT enclosed.\n");
	else
		printf("Map is fully enclosed.\n");
	return (result);
}

