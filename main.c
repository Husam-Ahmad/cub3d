/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 12:38:52 by jpluta            #+#    #+#             */
/*   Updated: 2025/11/15 13:38:22 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (argc != 2)
	{
		ft_putstr_fd("Wrong input\n", 1);
		return (0);
	}
	else if (!is_file_name_valid(argv[1]))
		return (1);
	eval_data(check_file_data(argv[1], &data), &data);
	construct_data(&data, argv);
	hooks(&data);
	mlx_loop(data.mlx.ptr);
	return (0);
}
