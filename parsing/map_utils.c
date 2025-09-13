/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 13:27:46 by jpluta            #+#    #+#             */
/*   Updated: 2025/09/13 14:04:55 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	find_map(char *line)
{
	while (*line && *line != '0' && *line != '1')
			line++;
	if (*line == '0' || *line == '1')
		return (1);
	else
		return (0);
}

// void	parse_map(char *line, t_data *data)
// {
// 	char	*temp;

// 	data->map = (char **)malloc(sizeof(char *))
// }