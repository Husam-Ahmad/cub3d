/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 12:35:55 by huahmad           #+#    #+#             */
/*   Updated: 2025/11/09 13:23:15 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"  

t_mlx	*get_wall_texture(t_data *data)
{
	if (data->side == 0)
	{
		if (data->ray_dir_x > 0)
			return (data->east);
		return (data->west);
	}
	else
	{
		if (data->ray_dir_y > 0)
			return (data->south);
		return (data->north);
	}
}

int	get_texel_color(t_mlx *tex, int tx, int ty)
{
	int		bpp_bytes;
	char	*addr;

	if (!tex || !tex->addr)
		return (0);
	if (tx < 0)
		tx = 0;
	if (ty < 0)
		ty = 0;
	if (tx >= tex->width)
		tx = tex->width - 1;
	if (ty >= tex->height)
		ty = tex->height - 1;
	bpp_bytes = tex->bpp / 8;
	addr = tex->addr + ty * tex->line_length + tx * bpp_bytes;
	return (*(int *)addr);
}

void	set_tex_params(t_data *d, t_draw *v)
{
	v->tex = get_wall_texture(d);
	if (!v->tex || !v->tex->addr || v->tex->width <= 0 || v->tex->height <= 0
		|| d->line_height <= 0)
	{
		v->tex = NULL;
		v->tex_x = 0;
		v->step = 0.0;
		v->tex_pos = 0.0;
		return ;
	}
	if (d->side == 0)
		v->wall_x = d->posy + d->perp_wall_dist * d->ray_dir_y;
	else
		v->wall_x = d->posx + d->perp_wall_dist * d->ray_dir_x;
	v->wall_x -= floor(v->wall_x);
	v->tex_x = (int)(v->wall_x * (double)v->tex->width);
	if ((d->side == 0 && d->ray_dir_x > 0) || (d->side == 1
			&& d->ray_dir_y < 0))
		v->tex_x = v->tex->width - v->tex_x - 1;
	v->step = (double)v->tex->height / (double)d->line_height;
	v->tex_pos = (v->start - SCREEN_HEIGHT / 2 + d->line_height / 2) * v->step;
}

void	put_wall_pixel(t_data *d, t_draw *v, int x)
{
	if (!v->tex)
	{
		v->buf[v->y * SCREEN_WIDTH + x] = d->wall_color;
		return ;
	}
	v->tex_y = (int)v->tex_pos;
	if (v->tex_y < 0)
		v->tex_y = 0;
	if (v->tex_y >= v->tex->height)
		v->tex_y = v->tex->height - 1;
	v->color = get_texel_color(v->tex, v->tex_x, v->tex_y);
	if (v->color != -16777216)
		v->buf[v->y * SCREEN_WIDTH + x] = v->color;
	v->tex_pos += v->step;
}
