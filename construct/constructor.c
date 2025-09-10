/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:47:44 by huahmad           #+#    #+#             */
/*   Updated: 2025/09/10 15:03:47 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_mlx	start_window(void)
{
	t_mlx	mlx;
	t_data	img;
	char	*relative_path = "sprites/east_wall.xpm";
	int		img_width;
	int		img_height;

	mlx.ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.ptr, 1600, 800, "Cub3D");
	img.img = mlx_new_image(mlx.ptr, 1600, 800);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	img.img = mlx_xpm_file_to_image(mlx.ptr, relative_path, &img_width, &img_height);
	mlx_put_image_to_window(mlx.ptr, mlx.win, img.img, 0, 0);
	mlx_loop(mlx.ptr);
	return (mlx);
}

void	construct_data(t_data *data, char **argv)
{
	data->mlx = start_window();
	(void)argv;
}
