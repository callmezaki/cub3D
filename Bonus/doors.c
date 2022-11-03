/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 19:33:29 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/03 19:34:38 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture	which_door_texture(t_data *data, t_door *door)
{
	if (door->dis_door <= 35 && door->dis_door > 30)
		return (data->txtr.d_f1);
	else if (door->dis_door <= 30 && door->dis_door > 25)
		return (data->txtr.d_f2);
	else if (door->dis_door <= 25 && door->dis_door > 20)
		return (data->txtr.d_f3);
	else if (door->dis_door <= 20 && door->dis_door > 15)
		return (data->txtr.d_f4);
	else if (door->dis_door <= 15 && door->dis_door > 10)
		return (data->txtr.d_f5);
	else if (door->dis_door <= 10)
		return (data->txtr.d_f6);
	else
		return (data->txtr.d_f0);
}

void	cast_door_ray(t_door *door, t_data *data, int i)
{
	t_dwvars	dw;

	dw.rad = (FOV) * (M_PI / 180);
	dw.proj_wall_height = 0;
	dw.tx = which_door_texture(data, door);
	if (door->h_or_v == 2)
		dw.txtr_off.x = (door->y_door - data->map_y) / Z;
	else
		dw.txtr_off.x = (door->x_door - data->map_x) / Z;
	dw.txtr_off.x = dw.txtr_off.x - floor(dw.txtr_off.x);
	dw.txtr_off.x *= dw.tx.width;
	door->dis_door = door->dis_door * cos(data->r[i].alpha - data->player.teta);
	if (data->r[i].distance <= door->dis_door)
		return ;
	dw.distance_to_proj = (W_WIDTH / 2) / tan(dw.rad / 2);
	dw.proj_wall_height = (Z / door->dis_door) * dw.distance_to_proj;
	dw.a = dw.proj_wall_height;
	if (dw.proj_wall_height > W_HEIGHT)
		dw.proj_wall_height = W_HEIGHT;
	dw.wall_top_pixel = (W_HEIGHT / 2) - ((int)dw.proj_wall_height / 2);
	dw.wall_bottom_pixel = (W_HEIGHT / 2) + ((int)dw.proj_wall_height / 2);
	if (dw.wall_bottom_pixel > W_HEIGHT)
		dw.wall_bottom_pixel = W_HEIGHT;
	dw.k = ((int)dw.a / 2) - (W_HEIGHT / 2);
	dw.j = dw.wall_top_pixel;
	while (dw.j < dw.wall_bottom_pixel)
	{
		dw.txtr_off.y = (dw.j + dw.k) * (dw.tx.height / dw.a);
		dw.txtr_off.y = floor(dw.txtr_off.y);
		dw.txtr_off.y *= dw.tx.width;
		dw.h = (int)dw.txtr_off.x + (int)dw.txtr_off.y;
		if (dw.tx.tab[dw.h] != 16711935 && dw.h < (dw.tx.height * dw.tx.width))
		{
			my_mlx_pixel_put(&data->window, i, dw.j, dw.tx.tab[dw.h]);
		}
		dw.j++;
	}
}

void	free_list(t_door *door)
{
	t_door	*d;

	while (door->next)
	{
		d = door;
		door = door->next;
		free(d);
	}
	free(door);
}

int	return_firstx(t_data *data, t_sprite sp)
{
	t_dwsprite	s;

	s.rad = (FOV) * (M_PI / 180);
	s.distance_to_proj = (W_WIDTH / 2) / tan(s.rad / 2);
	s.sp_width = (Z / sp.distance) * s.distance_to_proj;
	s.t.y = sp.y - data->player.y;
	s.t.x = sp.x - data->player.x;
	sp.angle = normalize(atan2(s.t.y, s.t.x) - data->player.teta);
	s.sp_sc_posX = tan(sp.angle) * s.distance_to_proj;
	s.sp_leftX = (W_WIDTH / 2) + s.sp_sc_posX - (s.sp_width / 2);
	return ((int)s.sp_leftX);
}

void	draw_doors(t_data *data)
{
	int		i;
	int		x;
	t_door	*door;

	i = 0;
	while (i < RAYS)
	{
		if (data->r[i].hit_door == 1)
		{
			door = data->r[i].door;
			while (door->next)
			{
				x = 0;
				while (x < data->sp)
				{
					if (return_firstx(data, data->sprites[x]) <= i && \
	data->sprites[x].distance > door->dis_door && data->sprites[x].drown == 0)
						draw_sprite(data, x);
					x++;
				}
				cast_door_ray(door, data, i);
				door = door->next;
			}
		}
		free_list(data->r[i].door);
		i++;
	}
}