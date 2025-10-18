/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 12:38:52 by jpluta            #+#    #+#             */
/*   Updated: 2025/10/18 17:00:31 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// for testing purposes
void	print_stored_data(t_data *data)
{
	int	i, x;

	i = 0;
	x = 0;
	printf("NO: %s", data->path_to_the_north_texture);
	printf("SO: %s", data->path_to_the_south_texture);
	printf("WE: %s", data->path_to_the_west_texture);
	printf("EA: %s", data->path_to_the_east_texture);
	printf("colour floor: R %d, G: %d, B: %d\n", data->F.R, data->F.G, data->F.B);
	printf("colour ceiling: R %d, G: %d, B: %d\n", data->C.R, data->C.G, data->C.B);
	printf("map rows: %d\n", data->valid_file_data.map_rows);
	printf("map: \n");
	// map_boundaries(data);
	while (i <= data->valid_file_data.map_rows)
	{
		printf("%s", data->map[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_putstr_fd("Wrong input\n", 1);
		return (0);
	}
	else if (!is_file_name_valid(argv[1]))
		return (1);
	ft_bzero(&data, sizeof(t_data));
	if (check_file_data(argv[1], &data) == 0)
	{
		printf("Error intcorrect data\n");
		return (1);
	}
	print_stored_data(&data);
	// // construct_data(&data, argv);
	return (0);
}

int	is_file_name_valid(char *file_name)
{
	char	*p_to_extension;

	p_to_extension = ft_strchr(file_name, '.');
	if (!p_to_extension)
	{
		printf("Expected file with .cub extension\n");
		return (0);
	}
	else if (ft_strncmp(p_to_extension, ".cub", 4) != 0)
	{
		printf("Wrong extension: expected .cub\n");
		return (0);
	}
	else
		return (1);
}

t_valid_file_data	init_valid_file_data(void)
{
	t_valid_file_data	default_data;

	ft_bzero(&default_data, sizeof(t_valid_file_data));
	return (default_data);
}
