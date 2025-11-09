/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:13:56 by huahmad           #+#    #+#             */
/*   Updated: 2025/11/09 13:25:35 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rotate_left(t_data *data)
{
	double	olddirx;
	double	oldplanex;
	double	rot;

	olddirx = data->dirx;
	oldplanex = data->planex;
	rot = -0.3;
	data->dirx = data->dirx * cos(rot) - data->diry * sin(rot);
	data->diry = olddirx * sin(rot) + data->diry * cos(rot);
	data->planex = data->planex * cos(rot) - data->planey * sin(rot);
	data->planey = oldplanex * sin(rot) + data->planey * cos(rot);
}

void	rotate_right(t_data *data)
{
	double	olddirx;
	double	oldplanex;
	double	rot;

	olddirx = data->dirx;
	oldplanex = data->planex;
	rot = 0.3;
	data->dirx = data->dirx * cos(rot) - data->diry * sin(rot);
	data->diry = olddirx * sin(rot) + data->diry * cos(rot);
	data->planex = data->planex * cos(rot) - data->planey * sin(rot);
	data->planey = oldplanex * sin(rot) + data->planey * cos(rot);
}
