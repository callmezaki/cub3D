/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 20:34:30 by zait-sli          #+#    #+#             */
/*   Updated: 2022/10/18 21:46:04 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	h_distance(t_data *data, double beta)
{
	t_point	a;
	t_point	first_inter;
	t_point	t;
	t_point	stp;
	double	h;
	t_point	ply;

	ply.x = data->player.x - data->map_x;
	ply.y = data->player.y - data->map_y;
	first_inter.y = floor(ply.y / Z) * Z;
	if (facing_down(beta))
		first_inter.y += Z;
	first_inter.x = ply.x + ((first_inter.y - ply.y) / tan(beta));
	stp.y = Z;
	if (!facing_down(beta))
		stp.y *= -1;
	stp.x = Z / tan(beta);
	if ((!facing_right(beta) && stp.x > 0) || (facing_right(beta) && stp.x < 0))
		stp.x *= -1;
	while (1)
	{
		t.x = first_inter.x;
		t.y = first_inter.y;
		if (!facing_down(beta))
			t.y -= 1;
		a.x = t.x / Z;
		a.y = t.y / Z;
		if (a.y >= data->map_height || a.y < 0
			|| a.x > get_map_width(data, a.y) || a.x < 0)
		{			
			h = sqrt(pow(first_inter.x - ply.x, 2)
					+ pow(first_inter.y - ply.y, 2));
			return (h);
		}
		if (data->map[(int)a.y][(int)a.x] != '0'
			&& !check_player(data->map[(int)a.y][(int)a.x]))
		{
			h = sqrt(pow(first_inter.x - ply.x, 2)
					+ pow(first_inter.y - ply.y, 2));
			return (h);
		}
		first_inter.x += stp.x;
		first_inter.y += stp.y;
	}
}

double	v_distance(t_data *data, double beta)
{
	t_point	a;
	t_point	first_inter;
	t_point	t;
	t_point	stp;
	double	h;
	t_point	ply;

	ply.x = data->player.x - data->map_x;
	ply.y = data->player.y - data->map_y;
	first_inter.x = floor(ply.x / Z) * Z;
	if (facing_right(beta))
		first_inter.x += Z;
	first_inter.y = ply.y + ((first_inter.x - ply.x) * tan(beta));
	stp.x = Z;
	if (!facing_right(beta))
		stp.x *= -1;
	stp.y = Z * tan(beta);
	if ((!facing_down(beta) && stp.y > 0) || (facing_down(beta) && stp.y < 0))
		stp.y *= -1;
	while (1)
	{
		t.x = first_inter.x;
		t.y = first_inter.y;
		if (!facing_right(beta))
			t.x -= 1;
		a.x = t.x / Z;
		a.y = t.y / Z;
		if (a.y >= data->map_height || a.y < 0
			|| a.x > get_map_width(data, a.y) || a.x < 0)
		{			
			h = sqrt(pow(first_inter.x - ply.x, 2)
					+ pow(first_inter.y - ply.y, 2));
			return (h);
		}
		if (data->map[(int)a.y][(int)a.x] != '0'
				&& !check_player(data->map[(int)a.y][(int)a.x]))
		{
			h = sqrt(pow(first_inter.x - ply.x, 2)
					+ pow(first_inter.y - ply.y, 2));
			return (h);
		}
		first_inter.x += stp.x;
		first_inter.y += stp.y;
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
	double	t;
	int		i;
	t_ray	*r;

	i = 0;
	t *= -1;
	r = malloc(sizeof(t_ray) * rays);
	while (i < rays)
	{
		sigma = data->player.teta + (t);
		best_distance(data, sigma);
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
