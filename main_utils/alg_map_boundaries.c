/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_map_boundaries.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:51:22 by jpluta            #+#    #+#             */
/*   Updated: 2025/11/11 18:13:59 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	flood_fill(char **map, bool **visited, t_rows_cols *rows_and_cols,
		int col)
{
	bool	up;
	bool	down;
	bool	left;
	bool	right;
	char	c;

	if (rows_and_cols->row < 0 || rows_and_cols->row >= rows_and_cols->rows
		|| col < 0 || col >= rows_and_cols->cols)
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
	up = flood_fill(map, visited, rows_and_cols, col);
	rows_and_cols->row += 2;
	down = flood_fill(map, visited, rows_and_cols, col);
	rows_and_cols->row -= 1;
	left = flood_fill(map, visited, rows_and_cols, col - 1);
	right = flood_fill(map, visited, rows_and_cols, col + 1);
	return (up && down && left && right);
}

static bool	find_start_pos(char **map, int rows, int *sr, int *sc)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
			{
				*sr = i;
				*sc = j;
				return (true);
			}
			j++;
		}
		i++;
	}
	printf("Error: No player start position found.\n");
	return (false);
}

static bool	**alloc_visited(int rows, int cols)
{
	int		i;
	bool	**visited;

	visited = malloc(sizeof(bool *) * rows);
	if (!visited)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		visited[i] = calloc(cols, sizeof(bool));
		if (!visited[i])
			return (NULL);
		i++;
	}
	return (visited);
}

static void	free_visited(bool **visited, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
		free(visited[i++]);
	free(visited);
}

bool	is_map_enclosed(char **map, int rows, int cols)
{
	int			sr;
	int			sc;
	bool		**visited;
	bool		result;
	t_rows_cols	rows_and_cols;

	if (!find_start_pos(map, rows, &sr, &sc))
		return (false);
	visited = alloc_visited(rows, cols);
	if (!visited)
		return (false);
	set_values(&rows_and_cols, rows, cols, sr);
	result = flood_fill(map, visited, &rows_and_cols, sc);
	free_visited(visited, rows);
	if (!result)
		printf("Map is NOT enclosed.\n");
	else
		printf("Map is fully enclosed.\n");
	return (result);
}
