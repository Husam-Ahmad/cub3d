/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_map_boundaries.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:51:22 by jpluta            #+#    #+#             */
/*   Updated: 2025/09/13 13:36:08 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// bool is_enclosed(char map[ROWS][COLS + 1], bool visited[ROWS][COLS], int row, int col) {
//     // If out of bounds — invalid
//     if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
//         return (false);
//     }

//     // If wall — safe
//     if (map[row][col] == '1') {
//         return (true);
//     }

//     // If already visited — skip
//     if (visited[row][col]) {
//         return (true);
//     }

//     // Mark as visited
//     visited[row][col] = true;

//     // Recurse in 4 directions
//     bool up    = is_enclosed(map, visited, row - 1, col);
//     bool down  = is_enclosed(map, visited, row + 1, col);
//     bool left  = is_enclosed(map, visited, row, col - 1);
//     bool right = is_enclosed(map, visited, row, col + 1);

//     return (up && down && left && right);
// }

// bool visited[ROWS][COLS] = { false };
// if (!is_enclosed(map, visited, player_row, player_col)) {
//     // The map is NOT valid
//     printf("Map is invalid: it's not fully enclosed!\n");
//     return false;
// } else {
//     // The map is valid
//     printf("Map is valid: fully enclosed from player's position.\n");
//     return true;
// }
