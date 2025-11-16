/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 13:27:46 by jpluta            #+#    #+#             */
/*   Updated: 2025/11/16 12:48:20 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		find_last_lane(char **map);

void	find_map_gaps(char **map)
{
    int	i;
    int	j;
    int	row_len;

    i = 0;
    while (map[i])
    {
        row_len = ft_strlen(map[i]);
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
                || map[i][j] == 'E' || map[i][j] == 'W')
            {
                if (j == 0 || j == row_len - 1)
                    printf("GAP at row %d, col %d: boundary not enclosed\n", i, j);
                else if (map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
                    printf("GAP at row %d, col %d: horizontal space adjacent\n", i, j);
                else if (i == 0 || !map[i - 1] || j >= (int)ft_strlen(map[i - 1]))
                    printf("GAP at row %d, col %d: no row above or out of bounds\n", i, j);
                else if (map[i + 1] && (map[i - 1][j] == ' ' || map[i + 1][j] == ' '))
                    printf("GAP at row %d, col %d: vertical space adjacent\n", i, j);
            }
            j++;
        }
        i++;
    }
}

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
