/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 12:38:03 by huahmad           #+#    #+#             */
/*   Updated: 2025/09/25 11:17:42 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void move_forward(t_data *data)
{
    double nx;
    double ny;
    
    nx = data->posX + data->dirX * move_speed;
    ny = data->posY + data->dirY * move_speed;
    if (data->map[(int)ny][(int)(nx)] == '0')
    {
        data->posY = ny;
        data->posX = nx;
    }    
}

void move_backward(t_data *data)
{
    double nx;
    double ny;
    
    nx = data->posX - data->dirX * move_speed;
    ny = data->posY - data->dirY * move_speed;
    if (data->map[(int)ny][(int)(nx)] == '0')
    {
        data->posY = ny;
        data->posX = nx;
    }    
}

void	move_left(t_data *data)
{
    double nx;
    double ny;
    
    ny = data->posY - data->planeY * move_speed;
    nx = data->posX - data->planeX * move_speed;
    if (data->map[(int)ny][(int)nx] == '0')
    {
        data->posX = nx;
        data->posY = ny;
    }
}

void	move_right(t_data *data)
{
    double nx;
    double ny; 
    
    ny = data->posY + data->planeY * move_speed;
    nx = data->posX + data->planeX * move_speed;
    if (data->map[(int)ny][(int)nx] == '0')
    {
        data->posX = nx;
        data->posY = ny;
    }
}
