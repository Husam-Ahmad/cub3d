/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 12:38:48 by jpluta            #+#    #+#             */
/*   Updated: 2025/09/23 19:29:11 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# define SCREEN_WIDTH  800
# define SCREEN_HEIGHT 600

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "libft/get_next_line/get_next_line.h"
#include "libft/libft.h"
#include "mlx.h"

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
	char   *addr;
	void	*img;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx;

typedef struct s_colours
{
	int	R;
	int	G;
	int	B;
}				t_colours;

typedef struct	s_valid_file_data
{
	int NO_path_to_the_north_texture;
	int SO_path_to_the_south_texture;
	int WE_path_to_the_west_texture;
	int EA_path_to_the_east_texture;
	int F;
	int	C;
	int	map_rows;
}					t_valid_file_data;

typedef struct	s_data
{
	char				*path_to_the_north_texture;
	char				*path_to_the_south_texture;
	char				*path_to_the_west_texture;
	char				*path_to_the_east_texture;
	char				**map;
	t_colours			F;
	t_colours			C;
	t_mlx				mlx;
	t_valid_file_data	valid_file_data;
	double				posX; 
	double 				posY;   
    double				dirX;   
    double				dirY;   
    double				planeY; // for camera 
    double				planeX; // for camera 
	int					map_x;
	int 				map_y;
	int     			step_x ;
	int 				step_y ;
	int 				side ;
	int 				hit;
	int  				line_height; 
	int 				draw_start ;
	int 				draw_end;
	double				ray_dir_x;
	double 				ray_dir_y;
	double 				side_dist_x;
	double 				side_dist_y;
	double 				delta_dist_x;
	double 				delta_dist_y; 
	double 				perp_wall_dist;
}					t_data;

/* main.c */
t_valid_file_data	init_valid_file_data(void);
int					is_file_name_valid(char *file_name);

/* parsing/check_file_data.c */
int					check_file_data(char *file, t_data *data);
void				process_line_for_valid_check(char *line, t_data *data);
void				extract_data(char *line, t_data *data);
void				extract_data_2(char *line, t_data *data);

/* parsing/process_file_data.c */
int					process_file_data(t_data *data, char *p_to_file);
void				process_line_for_parsing(char *line, t_data *data);
void				extract_data_parsing(char *line, t_data *data, char *map_line);
void				extract_data_parsing_2(char *line, t_data *data, char *map_line);
void				parse_colours(char *line, t_colours *colours);

/* parsing/parsing_utils.c */
int					test_if_openable(char *path);
char				*skip_empty_spaces(char *line);
int					valid_data(t_valid_file_data valid_file_data);

/* parsing/map_utils.c */
int					find_map(char *line);
void				parse_map(char *line, t_data *data);

/* construct/constructor.c */
void				construct_data(t_data *data, char **argv);
t_mlx				start_window(void);

#endif