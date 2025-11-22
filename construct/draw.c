/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 12:37:14 by huahmad           #+#    #+#             */
/*   Updated: 2025/11/22 16:05:18 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_vertical_line(t_data *d, int x)
{
	t_draw	v;

	v.y = 0;
	d->ceiling_color = 0x87CEBB;
	d->floor_color = 0x45138B;
	v.start = d->draw_start;
	v.end = d->draw_end;
	v.buf = (int *)d->mlx.addr;
	set_tex_params(d, &v);
	while (v.y < SCREEN_HEIGHT)
	{
		if (v.y < v.start)
			v.buf[v.y * SCREEN_WIDTH + x] = d->ceiling_color;
		else if (v.y <= v.end)
			put_wall_pixel(d, &v, x);
		else
			v.buf[v.y * SCREEN_WIDTH + x] = d->floor_color;
		v.y++;
	}
}

void	calc_line(t_data *data)
{
	if (data->side == 0)
		data->perp_wall_dist = (data->map_x - data->posx + (1 - data->step_x)
				/ 2) / data->ray_dir_x;
	else
		data->perp_wall_dist = (data->map_y - data->posy + (1 - data->step_y)
				/ 2) / data->ray_dir_y;
	data->line_height = (int)(SCREEN_HEIGHT / data->perp_wall_dist);
	data->draw_start = -data->line_height / 2 + SCREEN_HEIGHT / 2;
	if (data->draw_start < 0)
		data->draw_start = 0;
	data->draw_end = data->line_height / 2 + SCREEN_HEIGHT / 2;
	if (data->draw_end >= SCREEN_HEIGHT)
		data->draw_end = SCREEN_HEIGHT - 1;
}

void	init_ray(t_data *data, int x)
{
	const double	camera_x = 2.0 * x / (double)SCREEN_WIDTH - 1.0;

	data->ray_dir_x = data->dirx + data->planex * camera_x;
	data->ray_dir_y = data->diry + data->planey * camera_x;
	data->map_x = (int)data->posx;
	data->map_y = (int)data->posy;
	set_deltas(data);
	data->hit = 0;
	init_step_x(data);
	init_step_y(data);
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
