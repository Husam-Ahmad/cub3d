/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 12:38:14 by huahmad           #+#    #+#             */
/*   Updated: 2025/11/16 13:12:41 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// here we check if the values of ray_dir_x/y is close to zero.
// if they are,
// we set the corresponding delta distance to a very large value (1e30)
// this prevents division by zero
void	set_deltas(t_data *d)
{
	if (fabs(d->ray_dir_x) < 1e-9)
		d->delta_dist_x = 1e30;
	else
		d->delta_dist_x = fabs(1.0 / d->ray_dir_x);
	if (fabs(d->ray_dir_y) < 1e-9)
		d->delta_dist_y = 1e30;
	else
		d->delta_dist_y = fabs(1.0 / d->ray_dir_y);
}

void	init_step_y(t_data *d)
{
	if (d->ray_dir_y < 0)
	{
		d->step_y = -1;
		d->side_dist_y = (d->posy - d->map_y) * d->delta_dist_y;
	}
	else
	{
		d->step_y = 1;
		d->side_dist_y = (d->map_y + 1.0 - d->posy) * d->delta_dist_y;
	}
}

void	init_step_x(t_data *d)
{
	if (d->ray_dir_x < 0)
	{
		d->step_x = -1;
		d->side_dist_x = (d->posx - d->map_x) * d->delta_dist_x;
	}
	else
	{
		d->step_x = 1;
		d->side_dist_x = (d->map_x + 1.0 - d->posx) * d->delta_dist_x;
	}
}

static int	dda_hit_check(t_data *data)
{
	int	row_len;

	if (data->map_y < 0 || data->map_y >= data->valid_file_data.map_rows)
		return (1);
	row_len = ft_strlen(data->map[data->map_y]);
	if (data->map_x < 0 || data->map_x >= row_len)
		return (1);
	if (data->map[data->map_y][data->map_x] == '1')
		return (1);
	return (0);
}

void	dda(t_data *data)
{
	while (!data->hit)
	{
		dda_step(data);
		if (dda_hit_check(data))
			data->hit = 1;
	}
}

