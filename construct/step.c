/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 12:38:14 by huahmad           #+#    #+#             */
/*   Updated: 2025/11/09 12:39:03 by huahmad          ###   ########.fr       */
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
		d->side_dist_y = (d->posY - d->map_y) * d->delta_dist_y;
	}
	else
	{
		d->step_y = 1;
		d->side_dist_y = (d->map_y + 1.0 - d->posY) * d->delta_dist_y;
	}
}

void	init_step_x(t_data *d)
{
	if (d->ray_dir_x < 0)
	{
		d->step_x = -1;
		d->side_dist_x = (d->posX - d->map_x) * d->delta_dist_x;
	}
	else
	{
		d->step_x = 1;
		d->side_dist_x = (d->map_x + 1.0 - d->posX) * d->delta_dist_x;
	}
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