/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:47:44 by huahmad           #+#    #+#             */
/*   Updated: 2025/09/24 12:48:19 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_vertical_line(t_data *data, int x)
{
	int		y;
	int		start;
	int		end;
	int		color;
	int		*buf;

	y = 0;
	start = data->draw_start;
	end = data->draw_end;
	if (data->side == 1)
		color = 0xAAAAAA;
	else
		color = 0xFFFFFF;
	buf = (int *)data->mlx.addr;
	while (y < SCREEN_HEIGHT)
	{
		if (y >= start && y <= end)
			buf[y * SCREEN_WIDTH + x] = color;
		else
			buf[y * SCREEN_WIDTH + x] = 0x222222;
		y++;
	}
}

void	calc_line(t_data *data)
{
	if (data->side == 0)
		data->perp_wall_dist = (data->map_x - data->posX + (1 - data->step_x)
				/ 2) / data->ray_dir_x;
	else
		data->perp_wall_dist = (data->map_y - data->posY + (1 - data->step_y)
				/ 2) / data->ray_dir_y;
	data->line_height = (int)(SCREEN_HEIGHT / data->perp_wall_dist);
	data->draw_start = -data->line_height / 2 + SCREEN_HEIGHT / 2;
	if (data->draw_start < 0)
		data->draw_start = 0;
	data->draw_end = data->line_height / 2 + SCREEN_HEIGHT / 2;
	if (data->draw_end >= SCREEN_HEIGHT)
		data->draw_end = SCREEN_HEIGHT - 1;
}

void	dda(t_data *data)
{
	while (!data->hit)
	{
		if (data->side_dist_x < data->side_dist_y)
		{
			data->side_dist_x += data->delta_dist_x;
			data->map_x += data->step_x;
			data->side = 0;
		}
		else
		{
			data->side_dist_y += data->delta_dist_y;
			data->map_y += data->step_y;
			data->side = 1;
		}
		if (data->map[data->map_y][data->map_x] == '1')
			data->hit = 1;
	}
}

void	init_ray(t_data *data, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	data->ray_dir_x = data->dirX + data->planeX * camera_x;
	data->ray_dir_y = data->dirY + data->planeY * camera_x;
	data->map_x = (int)data->posX;
	data->map_y = (int)data->posY;
	data->delta_dist_x = fabs(1 / data->ray_dir_x);
	data->delta_dist_y = fabs(1 / data->ray_dir_y);
	data->hit = 0;
	if (data->ray_dir_x < 0)
	{
		data->step_x = -1;
		data->side_dist_x = (data->posX - data->map_x) * data->delta_dist_x;
	}
	else
	{
		data->step_x = 1;
		data->side_dist_x = (data->map_x + 1.0 - data->posX)
			* data->delta_dist_x;
	}
	if (data->ray_dir_y < 0)
	{
		data->step_y = -1;
		data->side_dist_y = (data->posY - data->map_y) * data->delta_dist_y;
	}
	else
	{
		data->step_y = 1;
		data->side_dist_y = (data->map_y + 1.0 - data->posY)
			* data->delta_dist_y;
	}
}

void	draw_scene(t_data *data)
{
	int	x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		init_ray(data, x);
		dda(data);
		calc_line(data);
		draw_vertical_line(data, x);
		x++;
	}
}

void	init_player(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	if (!data->map)
	{
		printf("Error: map is NULL\n");
		exit(1);
	}
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (ft_strchr("NSEW", data->map[y][x]))
			{
				data->posX = x + 0.5;
				data->posY = y + 0.5;
				if (data->map[y][x] == 'N')
				{
					data->dirX = 0;
					data->dirY = -1;
					data->planeX = 0.66;
					data->planeY = 0;
				}
				if (data->map[y][x] == 'S')
				{
					data->dirX = 0;
					data->dirY = 1;
					data->planeX = -0.66;
					data->planeY = 0;
				}
				if (data->map[y][x] == 'E')
				{
					data->dirX = 1;
					data->dirY = 0;
					data->planeX = 0;
					data->planeY = 0.66;
				}
				if (data->map[y][x] == 'W')
				{
					data->dirX = -1;
					data->dirY = 0;
					data->planeX = 0;
					data->planeY = -0.66;
				}
				data->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

t_mlx	start_window(void)
{
	t_mlx	mlx;

	mlx.ptr = mlx_init();
	if (!mlx.ptr)
	{
		printf("mlx_init failed\n");
		exit(1);
	}
	mlx.win = mlx_new_window(mlx.ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	mlx.img = mlx_new_image(mlx.ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.line_length,
			&mlx.endian);
	return (mlx);
}

void	construct_data(t_data *data, char **argv)
{
	data->mlx = start_window();
	(void)argv;
	init_player(data);
	draw_scene(data);
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->mlx.img, 0, 0);
}
