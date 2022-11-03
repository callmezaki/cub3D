/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 19:35:17 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/03 19:55:07 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_sprites(t_data *data)
{
	int			i;
	int			j;
	t_sprite	t;

	i = 0;
	while (i < data->sp)
	{
		j = 0;
		while (j + 1 < data->sp)
		{
			if (data->sprites[j].distance < data->sprites[j + 1].distance)
			{
				t = data->sprites[j + 1];
				data->sprites[j + 1] = data->sprites[j];
				data->sprites[j] = t;
			}
			j++;
		}
		i++;
	}
}

t_texture	which_sprite_texture(t_data *data)
{
	if (data->an > 80)
		data->an = 0;
	if (data->an >= 0 && data->an <= 20)
	{
		data->an++;
		return (data->txtr.s0);
	}
	else if (data->an > 20 && data->an <= 40)
	{
		data->an++;
		return (data->txtr.s1);
	}
	else if (data->an > 40 && data->an <= 60)
	{
		data->an++;
		return (data->txtr.s2);
	}
	else if (data->an > 60 && data->an <= 80)
	{
		data->an++;
		return (data->txtr.s3);
	}
	else
		return (data->txtr.s3);
}

void	get_sprite_data(t_data *data)
{
	int			i;
	int			j;
	int			x;
	t_point		t;
	t_sprite	*sps;

	sps = malloc(sizeof(t_sprite) * data->sp);
	j = 0;
	x = 0;
	while (data->map[j])
	{
		i = 0;
		while (data->map[j][i])
		{
			if (data->map[j][i] == '3')
			{
				sps[x].y = (j * Z) + data->map_y + (Z / 2);
				sps[x].x = (i * Z) + data->map_x + (Z / 2);
				sps[x].tx = data->txtr.sp;
				t.y = sps[x].y - data->player.y;
				t.x = sps[x].x - data->player.x;
				sps[x].angle = data->player.teta - atan2(t.y, t.x);
				if (sps[x].angle > M_PI)
					sps[x].angle -= 2 * M_PI;
				if (sps[x].angle < -M_PI)
					sps[x].angle += 2 * M_PI;
				sps[x].angle = fabs(sps[x].angle);
				sps[x].vis = 0;
				if (sps[x].angle < D_RAYS + 0.2)
					sps[x].vis = 1;
				sps[x].distance = sqrt(pow(sps[x].x - data->player.x, 2) + \
				pow(sps[x].y - data->player.y, 2));
				sps[x].drown = 0;
				x++;
			}
			i++;
		}
		j++;
	}
	data->sprites = sps;
	sort_sprites(data);
}

int	check_dis(t_data *data, int x, int i)
{
	if (data->sprites[x].distance < data->r[i].distance)
		return (1);
	return (0);
}

void	draw_sprite_rays(t_dwsprite *dsp, t_data *data, int x)
{
	dsp->i = dsp->sp_leftX;
	while (dsp->i < dsp->sp_rightX)
	{
		if (dsp->i >= 0 && dsp->i < W_WIDTH && check_dis(data, x, dsp->i))
		{
			dsp->tp = (dsp->tx.width / dsp->sp_width);
			dsp->txtr_off.x = (dsp->i - dsp->sp_leftX) * dsp->tp;
			dsp->j = dsp->sp_topY;
			while (dsp->j < dsp->sp_bottomY)
			{
				dsp->distance_from_top = dsp->j + ((int)dsp->sp_height / 2) - \
				(W_HEIGHT / 2);
				dsp->txtr_off.y = dsp->distance_from_top * \
				(dsp->tx.height / dsp->sp_height);
				dsp->h = (dsp->tx.width * (int)dsp->txtr_off.y) + \
				(int)dsp->txtr_off.x;
				if (dsp->h >= 0 && dsp->h < (dsp->tx.height * dsp->tx.width) && \
				dsp->tx.tab[dsp->h] != 3642478)
					my_mlx_pixel_put(&data->window, dsp->i, dsp->j, \
					dsp->tx.tab[dsp->h]);
				dsp->j++;
			}
		}
		dsp->i++;
	}
}

void	draw_sprite(t_data *data, int x)
{
	t_dwsprite	dsp;

	dsp.rad = (FOV) * (M_PI / 180);
	data->sprites[x].drown = 1;
	if (data->sprites[x].vis == 1)
	{
		dsp.tx = which_sprite_texture(data);
		dsp.distance_to_proj = (W_WIDTH / 2) / tan(dsp.rad / 2);
		dsp.sp_height = (Z / data->sprites[x].distance) * dsp.distance_to_proj;
		dsp.sp_width = dsp.sp_height;
		dsp.sp_topY = (W_HEIGHT / 2) - (dsp.sp_height / 2);
		if (dsp.sp_topY < 0)
			dsp.sp_topY = 0;
		dsp.sp_bottomY = (W_HEIGHT / 2) + (dsp.sp_height / 2);
		if (dsp.sp_bottomY > W_HEIGHT)
			dsp.sp_bottomY = W_HEIGHT;
		dsp.t.y = data->sprites[x].y - data->player.y;
		dsp.t.x = data->sprites[x].x - data->player.x;
		data->sprites[x].angle = normalize(atan2(dsp.t.y, dsp.t.x) - \
		data->player.teta);
		dsp.sp_sc_posX = tan(data->sprites[x].angle) * dsp.distance_to_proj;
		dsp.sp_leftX = (W_WIDTH / 2) + dsp.sp_sc_posX - (dsp.sp_width / 2);
		dsp.sp_rightX = dsp.sp_leftX + dsp.sp_width;
		draw_sprite_rays(&dsp, data, x);
	}
}

void	draw_rest_sprites(t_data *data)
{
	int	x;

	x = 0;
	while (x < data->sp)
	{
		if (data->sprites[x].drown == 0)
			draw_sprite(data, x);
		x++;
	}
}
