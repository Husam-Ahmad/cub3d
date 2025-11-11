/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 12:38:48 by jpluta            #+#    #+#             */
/*   Updated: 2025/11/11 18:14:53 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600
# define ESC_KEY 65307
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define LEFT_ARROW_KEY 65361
# define RIGHT_ARROW_KEY 65363

# define MOVE_SPEED 1

# include "libft/get_next_line/get_next_line.h"
# include "libft/libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_mlx
{
	int					width;
	int					height;
	int					bpp;
	void				*ptr;
	void				*win;
	char				*addr;
	void				*img;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}						t_mlx;

typedef struct s_draw
{
	int					y;
	int					start;
	int					end;
	t_mlx				*tex;
	int					*buf;
	int					color;
	double				step;
	double				tex_pos;
	double				wall_x;
	int					tex_x;
	int					tex_y;
}						t_draw;

typedef struct s_colours
{
	int					r;
	int					g;
	int					b;
}						t_colours;

typedef struct s_rows_cols
{
	int					rows;
	int					cols;
	int					row;
}						t_rows_cols;

typedef struct s_valid_file_data
{
	int					no_path_to_the_north_texture;
	int					so_path_to_the_south_texture;
	int					we_path_to_the_west_texture;
	int					ea_path_to_the_east_texture;
	int					f;
	int					c;
	int					map_rows;
}						t_valid_file_data;

typedef struct s_data
{
	char				*path_to_the_north_texture;
	char				*path_to_the_south_texture;
	char				*path_to_the_west_texture;
	char				*path_to_the_east_texture;
	char				**map;
	t_colours			f;
	t_colours			c;
	t_mlx				mlx;
	t_mlx				*north;
	t_mlx				*south;
	t_mlx				*east;
	t_mlx				*west;
	t_valid_file_data	valid_file_data;
	double				posx;
	double				posy;
	double				dirx;
	double				diry;
	double				planey;	
	double				planex;
	int					map_x;
	int					map_y;
	int					step_x;
	int					step_y;
	int					side;
	int					hit;
	int					line_height;
	int					draw_start;
	int					draw_end;
	double				ray_dir_x;
	double				ray_dir_y;
	double				side_dist_x;
	double				side_dist_y;
	double				delta_dist_x;
	double				delta_dist_y;
	double				perp_wall_dist;
	int					wall_color;
	int					floor_color;
	int					ceiling_color;
}						t_data;

/* main_utils/free_memory.c */
void					eval_data(int return_val, t_data *data);
void					free_textures(t_data *data);
void					free_and_exit(t_data *data);
t_valid_file_data		init_valid_file_data(void);
int						is_file_name_valid(char *file_name);

/* main_utils/alg_map_boundaries.c */
bool					flood_fill(char **map, bool **visited,
							t_rows_cols	*rows_and_cols, int col);
bool					is_map_enclosed(char **map, int rows, int cols);

/* main_utils/alg_map_utils.c */
int						check_boundaries(t_data *data);
int						find_longest_line(char **map);

/* parsing/check_file_data.c */
int						check_file_data(char *file, t_data *data);
void					process_line_for_valid_check(char *line, t_data *data);
void					extract_data(char *line, t_data *data);
void					extract_data_2(char *line, t_data *data);

/* parsing/process_file_data.c */
int						process_file_data(t_data *data, char *p_to_file);
void					process_line_for_parsing(char *line, t_data *data);
void					extract_data_parsing(char *line, t_data *data,
							char *map_line);
void					extract_data_parsing_2(char *line, t_data *data,
							char *map_line);
void					parse_colours(char *line, t_colours *colours);

/* parsing/parsing_utils.c */
int						test_if_openable_and_valid(char *path, int *status);
char					*skip_empty_spaces(char *line);
int						valid_data(t_valid_file_data valid_file_data);
char					*helper(char *path);

/* parsing/map_utils.c */
int						find_map(char *line);
void					parse_map(char *line, t_data *data);

/* construct/constructor.c */
void					construct_data(t_data *data, char **argv);
t_mlx					start_window(void);

/* hooking/keyhook.c */
int						handle_key(int keycode, t_data *data);
void					hooks(t_data *data);

/* hooking/movement.c */
void					move_forward(t_data *data);
void					move_backward(t_data *data);
void					rotate_left(t_data *data);
void					rotate_right(t_data *data);

/* hooking/rotation.c */
void					move_left(t_data *data);
void					move_right(t_data *data);

/* construct/texture2.c */
void					*my_addr(t_mlx *dir);
void					alloc_textures(t_data *data);
void					check_img(void *img);
void					tex_initialiser(t_data *data);

/* construct/texture.c */
t_mlx					*get_wall_texture(t_data *data);
int						get_texel_color(t_mlx *tex, int tx, int ty);
void					set_tex_params(t_data *d, t_draw *v);
void					put_wall_pixel(t_data *d, t_draw *v, int x);

/* construct/step.c */
void					set_deltas(t_data *d);
void					init_step_y(t_data *d);
void					init_step_x(t_data *d);
void					dda(t_data *data);

/* construct/player.c */
void					ifwore(t_data *d, char c);
void					set_dir_plane(t_data *d, char c);
int						set_player_if_needed(t_data *d, int x, int y);
void					init_player(t_data *data);

/*construct/draw.c*/
void					draw_vertical_line(t_data *d, int x);
void					calc_line(t_data *data);
void					init_ray(t_data *data, int x);
void					draw_scene(t_data *data);

void					set_values(t_rows_cols *rows_and_cols, int rows,
							int cols, int row);
void					free_tmlx(t_mlx *texture);

#endif