/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 12:34:31 by huahmad           #+#    #+#             */
/*   Updated: 2025/09/25 11:13:42 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int handle_key(int keycode, t_data *data)
{
    if (keycode == ESC_KEY)
        exit(0);
    else if (keycode == W_KEY)
        move_forward(data);
    else if (keycode == S_KEY)
        move_backward(data);
    else if (keycode == A_KEY)   
        move_left(data);
    else if (keycode == D_KEY)
        move_right(data);
    else if (keycode == LEFT_ARROW_KEY)
        rotate_left(data);
    else if (keycode == RIGHT_ARROW_KEY)
        rotate_right(data);
    draw_scene(data);
    mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->mlx.img, 0, 0);
    return (0);
}

void hooks(t_data *data)
{
    mlx_hook(data->mlx.win, 2, 1L<<0, handle_key, data);
    // mlx_hook(data->mlx.win, 17, 0, exit, NULL);
    // mlx_loop(data->mlx.ptr);
}