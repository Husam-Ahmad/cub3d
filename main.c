/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 12:38:52 by jpluta            #+#    #+#             */
/*   Updated: 2025/09/08 17:16:06 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	// data = init_t_data();
	if (argc != 2)
	{
		ft_putstr_fd("Wrong input\n", 1);
		return (0);
	}
	else if (!is_file_name_valid(argv[1]))
		return (1);
	ft_bzero(&data, sizeof(t_data));
	construct_data(&data, argv);
	check_and_process_file(argv[1], &data);
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
