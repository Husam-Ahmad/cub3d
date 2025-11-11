/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_colours.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 16:18:14 by jpluta            #+#    #+#             */
/*   Updated: 2025/11/11 16:21:17 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	parse_colours(char *line, t_colours *colour)
{
	int	i;

	i = 0;
	if (line[i] && ft_isdigit((int)(line[i])))
		colour->r = ft_atoi(&line[i]);
	while (line[i] && (line[i] >= '0' && line[i] <= '9'))
		i++;
	while (line[i] && (line[i] == ' ' || line[i] == ',' || line[i] == '\t'))
		i++;
	if (line[i] && ft_isdigit((int)(line[i])))
		colour->g = ft_atoi(&line[i]);
	while (line[i] && (line[i] >= '0' && line[i] <= '9'))
		i++;
	while (line[i] && (line[i] == ' ' || line[i] == ','
			|| line[i] == '\t'))
		i++;
	if (line[i] && ft_isdigit((int)(line[i])))
		colour->b = ft_atoi(&line[i]);
}
