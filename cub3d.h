/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 12:38:48 by jpluta            #+#    #+#             */
/*   Updated: 2025/09/08 17:17:23 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "libft/libft.h"

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
}	t_mlx;

typedef struct	s_data
{
	char	*path_to_the_north_texture;
	char	*path_to_the_south_texture;
	char	*path_to_the_west_texture;
	char	*path_to_the_east_texture;
	char	*F;
	char	*C;
	char	**map;
	t_mlx	mlx;
}					t_data;

typedef struct	s_valid_file_data
{
	int NO_path_to_the_north_texture;
	int SO_path_to_the_south_texture;
	int WE_path_to_the_west_texture;
	int EA_path_to_the_east_texture;
	int F;
	int	C;
	int	map;
}					t_valid_file_data;

t_valid_file_data	init_valid_file_data(void)
{
	t_valid_file_data	default_data;

	ft_bzero(&default_data, sizeof(t_valid_file_data));
	return (default_data);
}

/* main.c */
int		is_file_name_valid(char *file_name);

/* parsing/parse_file_data.c */
int		check_and_process_file(char *file, t_data *data);
void	process_line(char *line, t_data *data);
void	extract_data(char *line, t_data *data, int *i);
char	*skip_empty_spaces(char *line, int *i);

/* construct/constructor.c */
void	construct_data(t_data *data, char **argv);
t_mlx	start_window(void);

