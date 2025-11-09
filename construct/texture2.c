/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 12:40:12 by huahmad           #+#    #+#             */
/*   Updated: 2025/11/09 12:40:35 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	*my_addr(t_mlx *dir)
{
	if (!dir || !dir->img)
		return (NULL);
	dir->addr = mlx_get_data_addr(dir->img, &dir->bpp, &dir->line_length,
			&dir->endian);
	dir->bits_per_pixel = dir->bpp;
	return (dir->addr);
}

void	alloc_textures(t_data *data)
{
	if (!data)
		return ;
	if (!data->east)
		data->east = malloc(sizeof(t_mlx));
	if (!data->north)
		data->north = malloc(sizeof(t_mlx));
	if (!data->south)
		data->south = malloc(sizeof(t_mlx));
	if (!data->west)
		data->west = malloc(sizeof(t_mlx));
	if (!data->east || !data->north || !data->south || !data->west)
	{
		free(data->east);
		free(data->north);
		free(data->south);
		free(data->west);
		exit(1);
	}
	ft_memset(data->east, 0, sizeof(t_mlx));
	ft_memset(data->north, 0, sizeof(t_mlx));
	ft_memset(data->south, 0, sizeof(t_mlx));
	ft_memset(data->west, 0, sizeof(t_mlx));
}

void	check_img(void *img)
{
	if (!img)
	{
		ft_putstr_fd("Error: failed to load texture: ", 2);
		ft_putstr_fd("\n", 2);
		exit(1);
	}
}

void	tex_initialiser(t_data *data)
{
	data->east->img = mlx_xpm_file_to_image(data->mlx.ptr,
			data->path_to_the_east_texture, &data->east->width,
			&data->east->height);
	check_img(data->east->img);
	data->east->addr = my_addr(data->east);
	data->north->img = mlx_xpm_file_to_image(data->mlx.ptr,
			data->path_to_the_north_texture, &data->north->width,
			&data->north->height);
	check_img(data->north->img);
	data->north->addr = my_addr(data->north);
	data->south->img = mlx_xpm_file_to_image(data->mlx.ptr,
			data->path_to_the_south_texture, &data->south->width,
			&data->south->height);
	check_img(data->south->img);
	data->south->addr = my_addr(data->south);
	data->west->img = mlx_xpm_file_to_image(data->mlx.ptr,
			data->path_to_the_west_texture, &data->west->width,
			&data->west->height);
	check_img(data->west->img);
	data->west->addr = my_addr(data->west);
}
