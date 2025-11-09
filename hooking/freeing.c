/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 14:11:37 by huahmad           #+#    #+#             */
/*   Updated: 2025/11/09 14:16:47 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    free_tmlx(t_mlx *texture)
{
    if (!texture)
        return ;
    if (texture->ptr && texture->img)
        mlx_destroy_image(texture->ptr, texture->img);
    free(texture);
}
