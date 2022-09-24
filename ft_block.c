/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_block.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:28:14 by sgmira            #+#    #+#             */
/*   Updated: 2022/09/24 02:32:28 by zait-sli         ###   ########.fr       */
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
			if (block.x0 < W_width && block.x0 >=  0 && block.y0 < W_height && block.y0 >= 0)
           		my_mlx_pixel_put(data, block.x0, block.y0, block.color);
            block.y0++;
        }
        block.x0++;
    }
}