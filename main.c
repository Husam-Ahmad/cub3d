/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 12:38:52 by jpluta            #+#    #+#             */
/*   Updated: 2025/09/11 18:41:24 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	check_file_data(argv[1], &data);
	// printf("colour C: %d\n", data.C.R);
	// printf("colour C: %d\n", data.C.G);
	// printf("colour C: %d\n", data.C.B);
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
