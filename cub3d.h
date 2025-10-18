/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 12:38:48 by jpluta            #+#    #+#             */
/*   Updated: 2025/10/18 17:51:47 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# define SCREEN_WIDTH  800
# define SCREEN_HEIGHT 600
# define ESC_KEY 65307
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define LEFT_ARROW_KEY 65361
# define RIGHT_ARROW_KEY 65363

# define move_speed 1

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

/* alg_map_boundaries */
int					check_boundaries(t_data *data);
int					find_longest_line(char **map);
bool 				flood_fill(char **map, bool **visited,
						int rows, int cols, int row, int col);
bool				is_map_enclosed(char **map, int rows, int cols);

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
void				draw_scene(t_data *data);
void				init_player(t_data *data);
void				init_ray(t_data *data, int x);
void				dda(t_data *data);
void				calc_line(t_data *data);
void				draw_vertical_line(t_data *data, int x);

/* hooking/keyhook.c */
int					handle_key(int keycode, t_data *data);
void				hooks(t_data *data);

/* hooking/movement.c */
void				move_forward(t_data *data);
void 				move_backward(t_data *data);
void				rotate_left(t_data *data);
void				rotate_right(t_data *data);

/* hooking/rotation.c */
void				move_left(t_data *data);
void				move_right(t_data *data);

#endif