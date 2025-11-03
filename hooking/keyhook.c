/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 12:34:31 by huahmad           #+#    #+#             */
/*   Updated: 2025/11/03 16:55:33 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	close_win(t_data *data)
{
	(void)data;
	exit(0);
	return (0);
}

int	handle_key(int keycode, t_data *data)
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

void	hooks(t_data *data)
// {
//     if (!data || !data->mlx.ptr || !data->mlx.win)
//     {
//         ft_putstr_fd("Error: mlx not initialized in hooks\n", 2);
//         return ;
//     }
//     mlx_hook(data->mlx.win, 2, 1L<<0, handle_key, data);
//     // mlx_hook(data->mlx.win, 17, 0, exit, NULL);
//     // mlx_loop(data->mlx.ptr);
// }
{
	if (!data)
	{
		ft_putstr_fd("hooks: data is NULL\n", 2);
		return ;
	}
	fprintf(stderr, "hooks: mlx.ptr=%p mlx.win=%p\n", data->mlx.ptr,
		data->mlx.win);
	/* prefer mlx_key_hook to avoid mlx_int_set_win_event_mask inside mlx_hook */
	if (data->mlx.ptr && data->mlx.win)
	{
		mlx_key_hook(data->mlx.win, handle_key, data);
		mlx_hook(data->mlx.win, 17, 0, close_win, data); /* window close */
	}
	else
		ft_putstr_fd("Error: mlx not initialized in hooks\n", 2);
}