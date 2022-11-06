/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 19:35:17 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/06 20:35:02 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_sprite	sp_data(t_sprite sps, t_data *data, int i, int j)
{
	t_point		t;

	sps.y = (j * Z) + data->map_y + (Z / 2);
	sps.x = (i * Z) + data->map_x + (Z / 2);
	sps.tx = data->txtr.sp;
	t.y = sps.y - data->player.y;
	t.x = sps.x - data->player.x;
	sps.angle = data->player.teta - atan2(t.y, t.x);
	if (sps.angle > M_PI)
		sps.angle -= 2 * M_PI;
	if (sps.angle < -M_PI)
		sps.angle += 2 * M_PI;
	sps.angle = fabs(sps.angle);
	sps.vis = 0;
	if (sps.angle < data->rays_degr + 0.2)
		sps.vis = 1;
	sps.distance = sqrt(pow(sps.x - data->player.x, 2) + \
	pow(sps.y - data->player.y, 2));
	sps.drown = 0;
	return (sps);
}

void	get_sprite_data(t_data *data)
{
	int			i;
	int			j;
	int			x;
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
				sps[x] = sp_data(sps[x], data, i, j);
				x++;
			}
			i++;
		}
		j++;
	}
	data->sprites = sps;
	sort_sprites(data);
}

void	draw_sprite_rays(t_dwsprite *dsp, t_data *data, int x)
{
	dsp->i = dsp->sp_leftx;
	while (dsp->i < dsp->sp_rightx)
	{
		if (dsp->i >= 0 && dsp->i < W_WIDTH && check_dis(data, x, dsp->i))
		{
			dsp->tp = (dsp->tx.width / dsp->sp_width);
			dsp->txtr_off.x = (dsp->i - dsp->sp_leftx) * dsp->tp;
			dsp->j = dsp->sp_topy;
			while (dsp->j < dsp->sp_bottomy)
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
		dsp.sp_height = (dsp.distance_to_proj / data->sprites[x].distance) * Z;
		dsp.sp_width = dsp.sp_height;
		dsp.sp_topy = (W_HEIGHT / 2) - (dsp.sp_height / 2);
		if (dsp.sp_topy < 0)
			dsp.sp_topy = 0;
		dsp.sp_bottomy = (W_HEIGHT / 2) + (dsp.sp_height / 2);
		if (dsp.sp_bottomy > W_HEIGHT)
			dsp.sp_bottomy = W_HEIGHT;
		dsp.t.y = data->sprites[x].y - data->player.y;
		dsp.t.x = data->sprites[x].x - data->player.x;
		data->sprites[x].angle = normalize(atan2(dsp.t.y, dsp.t.x) - \
		data->player.teta);
		dsp.sp_sc_posx = tan(data->sprites[x].angle) * dsp.distance_to_proj;
		dsp.sp_leftx = (W_WIDTH / 2) + dsp.sp_sc_posx - (dsp.sp_width / 2);
		dsp.sp_rightx = dsp.sp_leftx + dsp.sp_width;
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
