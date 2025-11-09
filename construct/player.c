/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 12:39:25 by huahmad           #+#    #+#             */
/*   Updated: 2025/11/09 12:39:49 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ifwore(t_data *d, char c)
{
	if (c == 'W')
	{
		d->dirX = -1;
		d->dirY = 0;
		d->planeX = 0;
		d->planeY = -0.66;
	}
	else if (c == 'E')
	{
		d->dirX = 1;
		d->dirY = 0;
		d->planeX = 0;
		d->planeY = 0.66;
	}
}

void	set_dir_plane(t_data *d, char c)
{
	if (c == 'N')
	{
		d->dirX = 0;
		d->dirY = -1;
		d->planeX = 0.66;
		d->planeY = 0;
	}
	else if (c == 'S')
	{
		d->dirX = 0;
		d->dirY = 1;
		d->planeX = -0.66;
		d->planeY = 0;
	}
	else if (c == 'E')
		ifwore(d, 'E');
	else if (c == 'W')
		ifwore(d, 'W');
}

int	set_player_if_needed(t_data *d, int x, int y)
{
	char	c;

	c = d->map[y][x];
	if (!ft_strchr("NSEW", c))
		return (0);
	d->posX = x + 0.5;
	d->posY = y + 0.5;
	set_dir_plane(d, c);
	d->map[y][x] = '0';
	return (1);
}

void	init_player(t_data *data)
{
	int	x;
	int	y;

	if (!data || !data->map)
	{
		printf("error: map is null\n");
		exit(1);
	}
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
			if (set_player_if_needed(data, x++, y))
				return ;
		y++;
	}
}
