/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DDA.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:47:40 by zait-sli          #+#    #+#             */
/*   Updated: 2022/09/24 16:18:29 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double ft_abs(double d)
{
	if(d < 0)
		d *=-1;
	return(d);
}


void DDA(t_data *data, t_segment segment,int color)
{
	double incx;
	double incy;
	double dx;
	double dy;
	int stp;
	int i = 0;

	dx = segment.x1 - segment.x0;
	dy = segment.y1 - segment.y0;
	if (fabs(dx) > fabs(dy))
		stp = fabs(dx);
	else
		stp = fabs(dy);
	incx = dx/stp;
	incy = dy/stp;
	while(i < stp)
	{
		if(segment.x0 < W_width && segment.x0 >= 0 && segment.y0 < W_height && segment.y0 >= 0)
			my_mlx_pixel_put(&data->window, segment.x0, segment.y0, color);
		segment.x0 += incx;
		segment.y0 += incy;
		i++;
	}
}