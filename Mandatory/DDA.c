/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:47:40 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/03 18:41:54 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dda(t_data *data, t_segment segment, int color)
{
	float	incx;
	float	incy;
	int		dx;
	int		dy;
	int		stp;

	data->i = 0;
	dx = (int)segment.x1 - (int)segment.x0;
	dy = (int)segment.y1 - (int)segment.y0;
	if (abs(dx) > abs(dy))
		stp = abs(dx);
	else
		stp = abs(dy);
	incx = (float)dx / stp;
	incy = (float)dy / stp;
	while (data->i <= stp)
	{
		my_mlx_pixel_put(&data->window, segment.x0, segment.y0, color);
		segment.x0 += incx;
		segment.y0 += incy;
		data->i++;
	}
}

void	dda2(t_data *data, t_segment s, int color)
{
	float	incx;
	float	incy;
	int		dx;
	int		dy;
	int		stp;

	data->i = 0;
	dx = (int)s.x1 - (int)s.x0;
	dy = (int)s.y1 - (int)s.y0;
	if (abs(dx) > abs(dy))
		stp = abs(dx);
	else
		stp = abs(dy);
	incx = (float)dx / stp;
	incy = (float)dy / stp;
	while (data->i <= stp)
	{
		if (s.x0 > Z && s.x0 < Z * (MINI_CUB -1)
			&& s.y0 > Z && s.y0 < Z * (MINI_CUB -1))
			my_mlx_pixel_put(&data->window, s.x0, s.y0, color);
		s.x0 += incx;
		s.y0 += incy;
		data->i++;
	}
}
