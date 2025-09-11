/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 12:38:48 by jpluta            #+#    #+#             */
/*   Updated: 2025/09/11 18:20:11 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "libft/get_next_line/get_next_line.h"
#include "libft/libft.h"

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
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
	int	map;
}					t_valid_file_data;

typedef struct	s_data
{
	char				*path_to_the_north_texture;
	char				*path_to_the_south_texture;
	char				*path_to_the_west_texture;
	char				*path_to_the_east_texture;
	t_colours			F;
	t_colours			C;
	char				**map;
	t_mlx				mlx;
	t_valid_file_data	valid_file_data;
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
void				extract_data_parsing(char *line, t_data *data);
void				parse_colours(char *line, t_colours *colours);

/* parsing/parsing_utils.c */
int					test_if_openable(char *path);
char				*skip_empty_spaces(char *line);
int					valid_data(t_valid_file_data valid_file_data);


/* construct/constructor.c */
void				construct_data(t_data *data, char **argv);
t_mlx				start_window(void);

