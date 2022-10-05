/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 20:34:30 by zait-sli          #+#    #+#             */
/*   Updated: 2022/10/02 20:36:05 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double h_distance(t_data *data, double beta)
{
	t_point a; 
	t_point First_inter;
	t_point t;
	t_point stp;
	double h;
	t_point ply;

	ply.x = data->player.x - data->map_x;
	ply.y = data->player.y - data->map_y;
	First_inter.y = floor(ply.y / Z) * Z;
	if (facing_down(beta))
		First_inter.y += Z;
	First_inter.x = ply.x + ((First_inter.y - ply.y) / tan(beta));
	stp.y = Z;
	if (!facing_down(beta))
		stp.y *= -1;
	stp.x = Z / tan(beta);
	if ((!facing_right(beta) && stp.x > 0) || (facing_right(beta) && stp.x < 0))
		stp.x *= -1;
	while(1)
	{
		t.x = First_inter.x;
		t.y = First_inter.y;
		if (!facing_down(beta))
			t.y -= 1;
		a.x = t.x / Z;
		a.y = t.y / Z;
		if (a.y >= data->map_height || a.y < 0 || a.x > get_map_width(data,a.y) || a.x < 0)
		{			
			h = sqrt(pow(First_inter.x - ply.x,2) + pow(First_inter.y - ply.y,2));
			return(h);
		}
		if (data->map[(int)a.y][(int)a.x] != '0' && !check_player(data->map[(int)a.y][(int)a.x]))
		{
			h = sqrt(pow(First_inter.x - ply.x,2) + pow(First_inter.y - ply.y,2));
			return(h);
		}
		First_inter.x += stp.x;
		First_inter.y += stp.y;
	}
}

double v_distance(t_data *data, double beta)
{
	t_point a; 
	t_point First_inter;
	t_point t;
	t_point stp;
	double h;
	t_point ply;

	ply.x = data->player.x - data->map_x;
	ply.y = data->player.y - data->map_y;
	
	
	First_inter.x = floor(ply.x / Z) * Z;
	if (facing_right(beta))
		First_inter.x += Z;
	First_inter.y = ply.y + ((First_inter.x - ply.x) * tan(beta));
	stp.x = Z;
	if (!facing_right(beta))
		stp.x *= -1;
	stp.y = Z * tan(beta);
	if ((!facing_down(beta) && stp.y > 0) || (facing_down(beta) && stp.y < 0))
		stp.y *= -1;
	while(1)
	{
		t.x = First_inter.x;
		t.y = First_inter.y;
		if (!facing_right(beta))
			t.x -= 1;
		a.x = t.x / Z;
		a.y = t.y / Z;
		if (a.y >= data->map_height || a.y < 0 || a.x > get_map_width(data,a.y) || a.x < 0)
		{			
			h = sqrt(pow(First_inter.x - ply.x,2) + pow(First_inter.y - ply.y,2));
			return(h);
		}
		if (data->map[(int)a.y][(int)a.x] != '0' && !check_player(data->map[(int)a.y][(int)a.x]))
		{
			h = sqrt(pow(First_inter.x - ply.x,2) + pow(First_inter.y - ply.y,2));
			return(h);
		}
		First_inter.x += stp.x;
		First_inter.y += stp.y;
	}
}

void best_distance(t_data *data, double beta)
{
	data->distance.distance = 0;
	double h;
	double v;
	
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
	double sigma;
	double t = D_rays;
	t *= -1;

	int i = 0;
	t_ray* r;
	r = malloc(sizeof(t_ray) * rays);

	while(i < rays)
	{
		sigma = data->player.teta + (t);
		best_distance(data,sigma);
		r[i].x = data->player.x + (cos(sigma) * data->distance.distance);
		r[i].y = data->player.y + (sin(sigma) * data->distance.distance);
		r[i].distance = data->distance.distance;
		r[i].alpha = sigma;
		r[i].h_or_v = data->distance.h_or_v;
		i++;
		t += inc_rays;
	}
	data->r = r;
}