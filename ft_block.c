/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_block.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:28:14 by sgmira            #+#    #+#             */
/*   Updated: 2022/09/26 21:41:30 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void    ft_block(t_data *data, double x, double y,int color)
{
	int tmp;
	double tx = Z + x;
	double ty = Z + y;
	
	tmp = y;
    while(x < tx)
    {
        y = tmp;
        while(y < ty)
        {
			if (x < W_width && x >=  0 && y < W_height && y >= 0)
           		my_mlx_pixel_put(&data->window, x, y, color);
            y++;
        }
        x++;
    }
}

void    ft_block2(t_data *data, double x, double y,int color)
{
	int tmp;
	double tx = Z + x;
	double ty = Z + y;
	
	tmp = y;
    while(x < tx)
    {
        y = tmp;
        while(y < ty)
        {
			if (x < W_width && x >=  0 && y < W_height && y >= 0)
			{
				if (x > Z && x < Z  * (mini_cub -1) && y > Z && y < Z * (mini_cub -1))
           			my_mlx_pixel_put(&data->window, x, y, color);
			}
            y++;
        }
        x++;
    }
}