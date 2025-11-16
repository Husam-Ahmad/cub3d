/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_map_boundaries.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:51:22 by jpluta            #+#    #+#             */
/*   Updated: 2025/11/16 11:50:52 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	check_row(char *row, int i, int *found, int *sr, int *sc)
{
	int	j;

	j = 0;
	while (row[j])
	{
		if (row[j] == 'N' || row[j] == 'S' || row[j] == 'E' || row[j] == 'W')
		{
			*sr = i;
			*sc = j;
			(*found)++;
		}
		j++;
	}
}

static bool	find_start_pos(char **map, int rows, int *sr, int *sc)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (i < rows)
	{
		check_row(map[i], i, &found, sr, sc);
		i++;
	}
	if (found == 1)
		return (true);
	if (found == 0)
		printf("Error: No player start position found.\n");
	else
		printf("Error: Multiple player start positions found.\n");
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
