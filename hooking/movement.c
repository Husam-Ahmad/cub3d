/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 12:38:03 by huahmad           #+#    #+#             */
/*   Updated: 2025/11/09 13:25:35 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_forward(t_data *data)
{
	double	nx;
	double	ny;

	nx = data->posx + data->dirx * MOVE_SPEED;
	ny = data->posy + data->diry * MOVE_SPEED;
	if (data->map[(int)ny][(int)(nx)] == '0')
	{
		data->posy = ny;
		data->posx = nx;
	}
}

void	move_backward(t_data *data)
{
	double	nx;
	double	ny;

	nx = data->posx - data->dirx * MOVE_SPEED;
	ny = data->posy - data->diry * MOVE_SPEED;
	if (data->map[(int)ny][(int)(nx)] == '0')
	{
		data->posy = ny;
		data->posx = nx;
	}
}

void	move_left(t_data *data)
{
	double	nx;
	double	ny;

	ny = data->posy - data->planey * MOVE_SPEED;
	nx = data->posx - data->planex * MOVE_SPEED;
	if (data->map[(int)ny][(int)nx] == '0')
	{
		data->posx = nx;
		data->posy = ny;
	}
}

void	move_right(t_data *data)
{
	double	nx;
	double	ny;

	ny = data->posy + data->planey * MOVE_SPEED;
	nx = data->posx + data->planex * MOVE_SPEED;
	if (data->map[(int)ny][(int)nx] == '0')
	{
		data->posx = nx;
		data->posy = ny;
	}
}
