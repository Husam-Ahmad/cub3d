/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:47:44 by huahmad           #+#    #+#             */
/*   Updated: 2025/11/03 16:33:28 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// mlx_xpm_file_to_image(data->mlx->ptr, file, &width, &height));
//mlx_get_data_addr(dir->mlx_img, &dir->bpp,

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
    int	bpp_bytes;
    char *addr;

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

void	draw_vertical_line(t_data *data, int x)
{
	int		y;
	int		start;
	int		end;
	t_mlx	*tex;
	int		*buf;
	int     color;
	double	step;
	double	tex_pos;
	int		tex_x;
	int		tex_y;
	double	wall_x;
	
	y = 0;
	data->ceiling_color = 0x87CEEB;
	data->floor_color = 0x45138B;
	start = data->draw_start;
	end = data->draw_end;
	buf = (int *)data->mlx.addr;
	tex = get_wall_texture(data);
	    if (tex && tex->addr && tex->width > 0 && tex->height > 0 && data->line_height > 0)
    {
        if (data->side == 0)
            wall_x = data->posY + data->perp_wall_dist * data->ray_dir_y;
        else
            wall_x = data->posX + data->perp_wall_dist * data->ray_dir_x;
        wall_x -= floor(wall_x);
        tex_x = (int)(wall_x * (double)tex->width);
        if ((data->side == 0 && data->ray_dir_x > 0)
            || (data->side == 1 && data->ray_dir_y < 0))
            tex_x = tex->width - tex_x - 1;
        step = (double)tex->height / (double)data->line_height;
        tex_pos = (start - SCREEN_HEIGHT / 2 + data->line_height / 2) * step;
    }
    else
    {
        tex = NULL;
        tex_x = 0;
        step = 0.0;
        tex_pos = 0.0;
    }
	while (y < SCREEN_HEIGHT)
	{
		if (y < start)
			buf[y * SCREEN_WIDTH + x] = data->ceiling_color;
		else if (y >= start && y <= end)
		{
            if (tex)
            {
                tex_y = (int)tex_pos;
                if (tex_y < 0)
                    tex_y = 0;
                if (tex_y >= tex->height)
                    tex_y = tex->height - 1;
                color = get_texel_color(tex, tex_x, tex_y);
                /* skip transparent key (-16777216) */
                if (color != -16777216)
                    buf[y * SCREEN_WIDTH + x] = color;
                tex_pos += step;
            }
            else
                buf[y * SCREEN_WIDTH + x] = data->wall_color;
        }
		else
			buf[y * SCREEN_WIDTH + x] = data->floor_color;
		y++;
	}
}

void	calc_line(t_data *data)
{
	if (data->side == 0)
		data->perp_wall_dist = (data->map_x - data->posX + (1 - data->step_x)
				/ 2) / data->ray_dir_x;
	else
		data->perp_wall_dist = (data->map_y - data->posY + (1 - data->step_y)
				/ 2) / data->ray_dir_y;
	data->line_height = (int)(SCREEN_HEIGHT / data->perp_wall_dist);
	data->draw_start = -data->line_height / 2 + SCREEN_HEIGHT / 2;
	if (data->draw_start < 0)
		data->draw_start = 0;
	data->draw_end = data->line_height / 2 + SCREEN_HEIGHT / 2;
	if (data->draw_end >= SCREEN_HEIGHT)
		data->draw_end = SCREEN_HEIGHT - 1;
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

void	init_ray(t_data *data, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	data->ray_dir_x = data->dirX + data->planeX * camera_x;
	data->ray_dir_y = data->dirY + data->planeY * camera_x;
	data->map_x = (int)data->posX;
	data->map_y = (int)data->posY;
	data->delta_dist_x = fabs(1 / data->ray_dir_x);
	data->delta_dist_y = fabs(1 / data->ray_dir_y);
	data->hit = 0;
	if (data->ray_dir_x < 0)
	{
		data->step_x = -1;
		data->side_dist_x = (data->posX - data->map_x) * data->delta_dist_x;
	}
	else
	{
		data->step_x = 1;
		data->side_dist_x = (data->map_x + 1.0 - data->posX)
			* data->delta_dist_x;
	}
	if (data->ray_dir_y < 0)
	{
		data->step_y = -1;
		data->side_dist_y = (data->posY - data->map_y) * data->delta_dist_y;
	}
	else
	{
		data->step_y = 1;
		data->side_dist_y = (data->map_y + 1.0 - data->posY)
			* data->delta_dist_y;
	}
}

void	draw_scene(t_data *data)
{
	int	x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		init_ray(data, x);
		dda(data);
		calc_line(data);
		draw_vertical_line(data, x);
		x++;
	}
}

void	init_player(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	if (!data->map)
	{
		printf("Error: map is NULL\n");
		exit(1);
	}
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (ft_strchr("NSEW", data->map[y][x]))
			{
				data->posX = x + 0.5;
				data->posY = y + 0.5;
				if (data->map[y][x] == 'N')
				{
					data->dirX = 0;
					data->dirY = -1;
					data->planeX = 0.66;
					data->planeY = 0;
				}
				if (data->map[y][x] == 'S')
				{
					data->dirX = 0;
					data->dirY = 1;
					data->planeX = -0.66;
					data->planeY = 0;
				}
				if (data->map[y][x] == 'E')
				{
					data->dirX = 1;
					data->dirY = 0;
					data->planeX = 0;
					data->planeY = 0.66;
				}
				if (data->map[y][x] == 'W')
				{
					data->dirX = -1;
					data->dirY = 0;
					data->planeX = 0;
					data->planeY = -0.66;
				}
				data->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

void	*my_addr(t_mlx *dir)
{
    if (!dir || !dir->img)
        return (NULL);
    dir->addr = mlx_get_data_addr(dir->img, &dir->bpp,
            &dir->line_length, &dir->endian);
    dir->bits_per_pixel = dir->bpp;
    return (dir->addr);
}

void alloc_textures(t_data *data)
{
    if (!data)
        return ;
    if (!data->east)
        data->east = malloc(sizeof(t_mlx));
    if (!data->north)
        data->north = malloc(sizeof(t_mlx));
    if (!data->south)
        data->south = malloc(sizeof(t_mlx));
    if (!data->west)
        data->west = malloc(sizeof(t_mlx));
    if (!data->east || !data->north || !data->south || !data->west)
    {
        perror("alloc_textures: malloc");
        if (data->east) free(data->east);
        if (data->north) free(data->north);
        if (data->south) free(data->south);
        if (data->west) free(data->west);
        exit(1);
    }
    memset(data->east, 0, sizeof(t_mlx));
    memset(data->north, 0, sizeof(t_mlx));
    memset(data->south, 0, sizeof(t_mlx));
    memset(data->west, 0, sizeof(t_mlx));
}

void	check_img(void *img, char *path)
{
    if (!img)
    {
        ft_putstr_fd("Error: failed to load texture: ", 2);
        ft_putstr_fd(path ? path : "(null)", 2);
        ft_putstr_fd("\n", 2);
        exit(1);
    }
}

void	tex_initialiser(t_data *data)
{
	printf("something%s\n", data->path_to_the_east_texture);
	data->east->img = mlx_xpm_file_to_image(data->mlx.ptr, data->path_to_the_east_texture,
			&data->east->width, &data->east->height);
	// check_img(data->east->img, data->path_to_the_east_texture);
	data->east->addr = my_addr(data->east);
	data->north->img = mlx_xpm_file_to_image(data->mlx.ptr, data->path_to_the_north_texture,
			&data->north->width, &data->north->height);
	data->north->addr = my_addr(data->north);
	data->south->img = mlx_xpm_file_to_image(data->mlx.ptr, data->path_to_the_south_texture,
			&data->south->width, &data->south->height);
	data->south->addr = my_addr(data->south);
	data->west->img = mlx_xpm_file_to_image(data->mlx.ptr, data->path_to_the_west_texture,
			&data->west->width, &data->west->height);
	data->west->addr = my_addr(data->west);
}

t_mlx	start_window(void)
{
	t_mlx	mlx;

	mlx.ptr = mlx_init();
	if (!mlx.ptr)
	{
		printf("mlx_init failed\n");
		exit(1);
	}
	mlx.win = mlx_new_window(mlx.ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	mlx.img = mlx_new_image(mlx.ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.line_length,
			&mlx.endian);
	return (mlx);
}

void	construct_data(t_data *data, char **argv)
{
	data->mlx = start_window();
	(void)argv;
	alloc_textures(data);
	tex_initialiser(data);
	init_player(data);
	draw_scene(data);
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->mlx.img, 0, 0);
}
