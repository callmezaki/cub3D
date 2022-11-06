/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:22:07 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/06 20:37:40 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	run(t_data *data)
{
	if (data->player.walkdirection != 0)
		draw(data);
	else if (data->player.turndirection != 0)
		draw(data);
	return (0);
}

void	draw_walls_calc(t_data *data, t_dwvars	*dw)
{
	dw->txtr_off.x = dw->txtr_off.x - floor(dw->txtr_off.x);
	dw->txtr_off.x *= dw->tx.width;
	dw->per_distance = data->r[dw->i].distance * cos(data->r[dw->i].alpha
			- data->player.teta);
	dw->distance_to_proj = (W_WIDTH / 2) / tan(dw->rad / 2);
	dw->proj_wall_height = (dw->distance_to_proj / dw->per_distance) * Z;
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

void	player_symbol(t_data *data, double x, double y, int color)
{
	int		tmp;
	t_point	t;

	t.x = 4 + x;
	t.y = 4 + y;
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

void	move_player(t_data *data)
{
	t_point	p;
	t_point	t;

	p.x = 0.0;
	p.y = 0.0;
	data->player.teta = normalize(data->player.teta);
	data->player.teta += data->player.turndirection * data->rotation_speed;
	if (data->player.sides == 0 && (data->player.walkdirection != 0))
	{
		p.x += (cos(data->player.teta) * data->player.walkdirection * STEP);
		p.y += (sin(data->player.teta) * data->player.walkdirection * STEP);
	}
	if (data->player.sides == 1 && (data->player.walkdirection != 0))
	{
		p.x -= (sin(data->player.teta) * data->player.walkdirection * STEP);
		p.y += (cos(data->player.teta) * data->player.walkdirection * STEP);
	}
	t.x = (data->player.x - data->map_x + p.x) / Z;
	t.y = (data->player.y - data->map_y + p.y) / Z;
	if (data->map[(int)t.y][(int)t.x] == '0'
		|| check_player(data->map[(int)t.y][(int)t.x]))
	{
		data->player.x += p.x;
		data->player.y += p.y;
	}
}
