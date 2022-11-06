/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 04:21:34 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/06 04:48:15 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture	which_texture(t_data *data, int i)
{
	t_point	p;

	p.y = data->r[i].y - data->map_y;
	p.x = data->r[i].x - data->map_x;
	if (data->r[i].h_or_v == 1)
	{
		if (normalize(data->r[i].alpha) >= M_PI
			&& normalize(data->r[i].alpha) < 2 * M_PI)
			return (data->txtr.north);
		else
			return (data->txtr.south);
	}
	else
	{
		if (normalize(data->r[i].alpha) >= (M_PI / 2)
			&& normalize(data->r[i].alpha) < 3 * (M_PI / 2))
			return (data->txtr.east);
		else
			return (data->txtr.west);
	}	
}

void	draw_walls_calc(t_data *data, t_dwvars	*dw)
{
	dw->txtr_off.x = dw->txtr_off.x - floor(dw->txtr_off.x);
	dw->txtr_off.x *= dw->tx.width;
	dw->per_distance = data->r[dw->i].distance * cos(data->r[dw->i].alpha
			- data->player.teta);
	dw->distance_to_proj = (W_WIDTH / 2) / tan(dw->rad / 2);
	dw->proj_wall_height = (Z / dw->per_distance) * dw->distance_to_proj;
	dw->a = (int)dw->proj_wall_height;
	if (dw->proj_wall_height > W_HEIGHT)
	dw->proj_wall_height = W_HEIGHT;
	dw->wall_top_pixel = (W_HEIGHT / 2) - ((int)dw->proj_wall_height / 2);
	dw->wall_bottom_pixel = (W_HEIGHT / 2) + ((int)dw->proj_wall_height / 2);
	dw->x = (dw->a / 2) - (W_HEIGHT / 2);
	dw->j = dw->wall_top_pixel;
}

void	draw_walls(t_data *data)
{
	t_dwvars	dw;

	dw.rad = (FOV) * (M_PI / 180);
	dw.i = 0;
	while (dw.i < RAYS)
	{
		dw.tx = which_texture(data, dw.i);
		if (data->r[dw.i].h_or_v == 2)
			dw.txtr_off.x = (data->r[dw.i].y - data->map_y) / Z;
		else
			dw.txtr_off.x = (data->r[dw.i].x - data->map_x) / Z;
		draw_walls_calc(data, &dw);
		while (dw.j < dw.wall_bottom_pixel)
		{
			dw.txtr_off.y = (dw.j + dw.x) * (dw.tx.height / (dw.a));
			dw.txtr_off.y = floor(dw.txtr_off.y);
			dw.txtr_off.y *= dw.tx.width;
			my_mlx_pixel_put(&data->window, dw.i, dw.j,
				dw.tx.tab[(int)dw.txtr_off.x + (int)dw.txtr_off.y]);
			dw.j++;
		}
		dw.i++;
	}
}
