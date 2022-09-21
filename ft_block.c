/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_block.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:28:14 by sgmira            #+#    #+#             */
/*   Updated: 2022/09/21 16:59:34 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    ft_block(t_window *data, t_block *block)
{
    block->x0 = 100;
    block->y0 = 100;
    block->color = 4564;
    while(block->x0 < 200)
    {
        block->y0 = 100;
        while(block->y0 < 200)
        {
            my_mlx_pixel_put(data, block->x0, block->y0, block->color);
            block->y0++;
        }
        block->x0++;
    }
    
}