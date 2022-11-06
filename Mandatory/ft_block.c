/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_block.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:28:14 by sgmira            #+#    #+#             */
/*   Updated: 2022/11/06 23:42:28 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_block(t_data *data, double x, double y, int color)
{
	int		tmp;
	double	tx;
	double	ty;

	tx = data->tile + x;
	ty = data->tile + y;
	tmp = y;
	while (x < tx)
	{
		y = tmp;
		while (y < ty)
		{
			my_mlx_pixel_put(&data->window, x, y, color);
			y++;
		}
		x++;
	}
}

void	ft_block2(t_data *data, double x, double y, int color)
{
	int		tmp;
	double	tx;
	double	ty;

	tmp = y;
	tx = data->tile + x;
	ty = data->tile + y;
	while (x < tx)
	{
		y = tmp;
		while (y < ty)
		{
			if (x > data->tile && x < data->tile * (MINI_CUB - 1)
				&& y > data->tile && y < data->tile * (MINI_CUB - 1))
				my_mlx_pixel_put(&data->window, x, y, color);
			y++;
		}
		x++;
	}
}
