/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:13:56 by huahmad           #+#    #+#             */
/*   Updated: 2025/09/25 11:21:34 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rotate_left(t_data *data)
{
    double oldDirX;
    double oldPlaneX;
    double rot;

    oldDirX = data->dirX;
    oldPlaneX = data->planeX;
    rot = -0.3;
    data->dirX = data->dirX * cos(rot) - data->dirY * sin(rot);
    data->dirY = oldDirX * sin(rot) + data->dirY * cos(rot);
    data->planeX = data->planeX * cos(rot) - data->planeY * sin(rot);
    data->planeY = oldPlaneX * sin(rot) + data->planeY * cos(rot);
}

void	rotate_right(t_data *data)
{
    double oldDirX;
    double oldPlaneX;
    double rot;

    oldDirX = data->dirX;
    oldPlaneX = data->planeX;
    rot = 0.3;
    data->dirX = data->dirX * cos(rot) - data->dirY * sin(rot);
    data->dirY = oldDirX * sin(rot) + data->dirY * cos(rot);
    data->planeX = data->planeX * cos(rot) - data->planeY * sin(rot);
    data->planeY = oldPlaneX * sin(rot) + data->planeY * cos(rot);
}
