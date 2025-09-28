/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 16:43:48 by huahmad           #+#    #+#             */
/*   Updated: 2025/09/28 17:17:37 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	assign_tex(t_data *data)
{
	if (data->side == 0)
	{
		if (data->ray_dir_x > 0)
			data->tex = &data->tex_we;
		else
			data->tex = &data->tex_ea;
	}
	else
	{
		if (data->ray_dir_y > 0)
			data->tex = &data->tex_no;
		else
			data->tex = &data->tex_so;
	}
}

// void	assign_tex(t_raycast *ray, t_game *game)
// {
// ray->tex = NULL;
// if (ray->side == 0)
// {
// if (ray->raydir.x > 0)
// ray->tex = &game->world->tex_we;
// else
// ray->tex = &game->world->tex_ea;
// }
// else
// {
// if (ray->raydir.y > 0)
// ray->tex = &game->world->tex_no;
// else
// ray->tex = &game->world->tex_so;
// }
// }
//

void	calc_texture_hit(t_data *data)
{
	double	wall_x;

	data->tex_x = 0;
	if (data->side == 0)
		wall_x = data->posY + data->perp_wall_dist * data->ray_dir_y;
	else
		wall_x = data->posX + data->perp_wall_dist * data->ray_dir_x;
	wall_x -= floor(wall_x);
	data->tex_x = (int)(wall_x * (double)(data->tex->line_length / 4));
	if (data->side == 0 && data->ray_dir_x > 0)
		data->tex_x = data->tex->line_length / 4 - data->tex_x - 1;
	if (data->side == 1 && data->ray_dir_y < 0)
		data->tex_x = data->tex->line_length / 4 - data->tex_x - 1;
}

static int	get_tex_color(int tex_x, int tex_y, t_mlx *tex)
{
	int	offset;

	offset = tex_y * tex->line_length + tex_x * (tex->bits_per_pixel / 8);
	return (*(int *)(tex->addr + offset));
}

void	draw_wall_line(t_data *data, int x)
{
	int		y;
	int		color;
	int		tex_y;
	double	tex_pos;
	double	step;
	double	tex_offset;

	step = (double)(data->tex->line_length / 4) / (double)data->line_height;
	tex_offset = 0;
	if (data->line_height > SCREEN_HEIGHT)
		tex_offset = (data->line_height - SCREEN_HEIGHT) / 2.0 * step;
	tex_pos = tex_offset;
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		if (y < data->draw_start)
			((int *)data->mlx.addr)[y * SCREEN_WIDTH
				+ x] = (data->C.R << 16) | (data->C.G << 8) | data->C.B;
		else if (y >= data->draw_start && y <= data->draw_end)
		{
			tex_y = (int)tex_pos;
			if (tex_y < 0)
				tex_y = 0;
			if (tex_y >= data->tex->line_length / 4)
				tex_y = data->tex->line_length / 4 - 1;
			color = get_tex_color(data->tex_x, tex_y, data->tex);
			((int *)data->mlx.addr)[y * SCREEN_WIDTH + x] = color;
			tex_pos += step;
		}
		else
			((int *)data->mlx.addr)[y * SCREEN_WIDTH
				+ x] = (data->F.R << 16) | (data->F.G << 8) | data->F.B;
		y++;
	}
}
