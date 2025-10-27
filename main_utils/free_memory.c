/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:24:53 by jpluta            #+#    #+#             */
/*   Updated: 2025/10/27 18:18:38 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	eval_data(int return_val, t_data *data)
{
	if (return_val == 0) // missing or incorrect data
	{
		printf("Error intcorrect data\n");
		exit(1);
	}
	else if (return_val == -1) // map is enclosed
		free_and_exit(data);
	else
		return ;
}

void	free_and_exit(t_data *data)
{
	int	i;

	i = 0;
	if (data)
	{
		free_textures(data);
		if (data->map)
		{
			while (data->map[i])
			{
				free(data->map[i]);
				i++;
			}
			free(data->map);
		}
	}
	exit(1);
}

void	free_textures(t_data *data)
{
	if (data->path_to_the_east_texture)
		free(data->path_to_the_east_texture);
	if (data->path_to_the_north_texture)
		free(data->path_to_the_north_texture);
	if (data->path_to_the_west_texture)
		free(data->path_to_the_west_texture);
	if (data->path_to_the_south_texture)	
		free(data->path_to_the_south_texture);
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