/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_block.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:28:14 by sgmira            #+#    #+#             */
/*   Updated: 2022/11/03 18:41:15 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_block(t_data *data, double x, double y,int color)
{
	int		tmp;
	t_point	t;

	t.x = Z + x;
	t.y = Z + y;
	tmp = y;
	while (x < t.x)
	{
		y = tmp;
		while (y < t.y)
		{
			my_mlx_pixel_put(&data->window, x, y, color);
			y++;
		}
		x++;
	}
}

void	ft_block2(t_data *data, double x, double y,int color)
{
	int		tmp;
	t_point	t;

	t.x = Z + x;
	t.y = Z + y;
	tmp = y;
	while (x < t.x)
	{
		y = tmp;
		while (y < t.y)
		{
			if (x > Z && x < Z * (MINI_CUB -1) && y > Z && \
			y < Z * (MINI_CUB -1))
				my_mlx_pixel_put(&data->window, x, y, color);
			y++;
		}
		x++;
	}
}
