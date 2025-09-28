/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 17:14:58 by huahmad           #+#    #+#             */
/*   Updated: 2025/09/28 17:41:50 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_single_tex(t_mlx *tex, void *mlx_ptr, char *path)
{
	tex->img = mlx_xpm_file_to_image(mlx_ptr, path, tex->texture_hight, tex->texture_width);
	if (!tex->img)
	{
		printf("Failed to load texture: %s\n", path);
		exit(1);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
	if (!tex->addr)
	{
		printf("Failed to get texture address: %s\n", path);
		exit(1);
	}
}

void	load_textures(t_data *data)
{
	load_single_tex(&data->tex_no, data->mlx.ptr,
		data->path_to_the_north_texture);
	load_single_tex(&data->tex_so, data->mlx.ptr,
		data->path_to_the_south_texture);
	load_single_tex(&data->tex_we, data->mlx.ptr,
		data->path_to_the_west_texture);
	load_single_tex(&data->tex_ea, data->mlx.ptr,
		data->path_to_the_east_texture);
}
