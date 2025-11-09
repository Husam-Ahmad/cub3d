/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_map_boundaries.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:51:22 by jpluta            #+#    #+#             */
/*   Updated: 2025/11/09 12:59:41 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	flood_fill(char **map, bool **visited, int rows, int cols, int row,
		int col)
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
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
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
	int		sr;
	int		sc;
	bool	**visited;
	bool	result;

	if (!find_start_pos(map, rows, &sr, &sc))
		return (false);
	visited = alloc_visited(rows, cols);
	if (!visited)
		return (false);
	result = flood_fill(map, visited, rows, cols, sr, sc);
	free_visited(visited, rows);
	if (!result)
		printf("Map is NOT enclosed.\n");
	else
		printf("Map is fully enclosed.\n");
	return (result);
}
