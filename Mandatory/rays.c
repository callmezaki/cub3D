/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 20:34:30 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/06 20:36:50 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	v_distance(t_data *data, double beta)
{
	double	h;

	v_distance_calc(data, beta);
	while (1)
	{
		v_distance_calc2(data, beta);
		if (data->a.y >= data->map_height || data->a.y < 0
			|| data->a.x > get_map_width(data, data->a.y) || data->a.x < 0)
		{			
			h = sqrt(pow(data->first_inter.x - data->ply.x, 2)
					+ pow(data->first_inter.y - data->ply.y, 2));
			return (h);
		}
		if (data->map[(int)data->a.y][(int)data->a.x] != '0'
				&& !check_player(data->map[(int)data->a.y][(int)data->a.x]))
		{
			h = sqrt(pow(data->first_inter.x - data->ply.x, 2)
					+ pow(data->first_inter.y - data->ply.y, 2));
			return (h);
		}
		data->first_inter.x += data->stp.x;
		data->first_inter.y += data->stp.y;
	}
}

void	best_distance(t_data *data, double beta)
{
	double	h;
	double	v;

	data->distance.distance = 0;
	beta = normalize(beta);
	v = v_distance(data, beta);
	h = h_distance(data, beta);
	if (h < v)
	{
		data->distance.h_or_v = 1;
		data->distance.distance = h;
	}
	else
	{
		data->distance.h_or_v = 2;
		data->distance.distance = v;
	}
}

void	claculate_rays(t_data *data)
{
	double	sigma;
	double	t;
	int		i;
	t_ray	*r;

	t = data->rays_degr;
	i = 0;
	t *= -1;
	r = malloc(sizeof(t_ray) * RAYS);
	while (i < RAYS)
	{
		sigma = data->player.teta + (t);
		best_distance(data, sigma);
		r[i].x = data->player.x + (cos(sigma) * data->distance.distance);
		r[i].y = data->player.y + (sin(sigma) * data->distance.distance);
		r[i].distance = data->distance.distance;
		r[i].alpha = sigma;
		r[i].h_or_v = data->distance.h_or_v;
		i++;
		t += data->rays_inc;
	}
	data->r = r;
}
