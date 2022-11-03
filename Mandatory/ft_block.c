/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_block.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:28:14 by sgmira            #+#    #+#             */
/*   Updated: 2022/11/03 01:07:11 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_block(t_data *data, double x, double y, int color)
{
	int		tmp;
	double	tx;
	double	ty;

	tx = Z + x;
	ty = Z + y;
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
	tx = Z + x;
	ty = Z + y;
	while (x < tx)
	{
		y = tmp;
		while (y < ty)
		{
			if (x > Z && x < Z * (MINI_CUB - 1)
				&& y > Z && y < Z * (MINI_CUB - 1))
				my_mlx_pixel_put(&data->window, x, y, color);
			y++;
		}
		x++;
	}
}
