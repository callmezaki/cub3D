/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 19:33:29 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/07 19:48:06 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

int	door_ray(t_dwvars *dw, t_door *door, t_data *data, int i)
{
	door->dis_door = door->dis_door * cos(data->r[i].alpha - data->player.teta);
	if (data->r[i].distance <= door->dis_door)
		return (0);
	dw->distance_to_proj = (W_WIDTH / 2) / tan(dw->rad / 2);
	dw->proj_wall_height = (dw->distance_to_proj / door->dis_door) * data->tile;
	dw->a = dw->proj_wall_height;
	if (dw->proj_wall_height > W_HEIGHT)
		dw->proj_wall_height = W_HEIGHT;
	dw->wall_top_pixel = (W_HEIGHT / 2) - ((int)dw->proj_wall_height / 2);
	dw->wall_bottom_pixel = (W_HEIGHT / 2) + ((int)dw->proj_wall_height / 2);
	if (dw->wall_bottom_pixel > W_HEIGHT)
		dw->wall_bottom_pixel = W_HEIGHT;
	dw->k = ((int)dw->a / 2) - (W_HEIGHT / 2);
	dw->j = dw->wall_top_pixel;
	return (1);
}

void	cast_door_ray(t_door *door, t_data *data, int i)
{
	t_dwvars	dw;

	dw.rad = (FOV) * (M_PI / 180);
	dw.proj_wall_height = 0;
	dw.tx = which_door_texture(data, door);
	if (door->h_or_v == 2)
		dw.txtr_off.x = (door->y_door - data->map_y) / data->tile;
	else
		dw.txtr_off.x = (door->x_door - data->map_x) / data->tile;
	dw.txtr_off.x = dw.txtr_off.x - floor(dw.txtr_off.x);
	dw.txtr_off.x *= dw.tx.width;
	if (!door_ray(&dw, door, data, i))
		return ;
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
