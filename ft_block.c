/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_block.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:28:14 by sgmira            #+#    #+#             */
/*   Updated: 2022/09/21 17:59:31 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void    ft_block(t_window *data, t_block block)
{
	int tmp;
	
	tmp = block.y0;
    while(block.x0 < block.x1)
    {
        block.y0 = tmp;
        while(block.y0 < block.y1)
        {
            my_mlx_pixel_put(data, block.x0, block.y0, block.color);
            block.y0++;
        }
        block.x0++;
    }
}