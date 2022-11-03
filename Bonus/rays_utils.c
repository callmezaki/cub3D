/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 19:24:31 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/03 19:25:43 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_h_inter(t_data *data, t_dis *d)
{	
	d->ply.x = data->player.x - data->map_x;
	d->ply.y = data->player.y - data->map_y;
	d->first_inter.y = floor(d->ply.y / Z) * Z;
	if (facing_down(d->beta))
		d->first_inter.y += Z;
	d->first_inter.x = d->ply.x + \
	((d->first_inter.y - d->ply.y) / tan(d->beta));
	d->stp.y = Z;
	if (!facing_down(d->beta))
		d->stp.y *= -1;
	d->stp.x = Z / tan(d->beta);
	if ((!facing_right(d->beta) && d->stp.x > 0) || \
	(facing_right(d->beta) && d->stp.x < 0))
		d->stp.x *= -1;
}

int	check_hit(t_data *data, t_dis *d, t_ray *ray, t_door door)
{
	if (d->a.y >= data->map_height || d->a.y < 0 || \
	d->a.x > get_map_width(data, d->a.y) || d->a.x < 0)
	{	
		d->dis = sqrt(pow(d->first_inter.x - d->ply.x, 2) + \
		pow(d->first_inter.y - d->ply.y, 2));
		return (1);
	}
	if (data->map[(int)d->a.y][(int)d->a.x] == '2')
	{
		ray->hit_door = 1;
		door.h_or_v = d->h_or_v;
		door.dis_door = sqrt(pow(d->first_inter.x - d->ply.x, 2) + \
		pow(d->first_inter.y - d->ply.y, 2));
		door.x_door = data->player.x + (cos(d->beta) * door.dis_door);
		door.y_door = data->player.y + (sin(d->beta) * door.dis_door);
		ft_add_front(&ray->door, ft_new(door));
	}
	if (data->map[(int)d->a.y][(int)d->a.x] == '1')
	{
		d->dis = sqrt(pow(d->first_inter.x - d->ply.x, 2) + \
		pow(d->first_inter.y - d->ply.y, 2));
		return (1);
	}
	return (0);
}

double	h_distance(t_data *data, double beta, t_ray *ray)
{
	t_dis	d;
	t_door	door;

	d.beta = beta;
	d.h_or_v = 1;
	get_h_inter(data, &d);
	while (1)
	{
		door.h_or_v = 0;
		door.dis_door = 0;
		door.x_door = 0;
		door.y_door = 0;
		d.t.x = d.first_inter.x;
		d.t.y = d.first_inter.y;
		if (!facing_down(d.beta))
				d.t.y -= 1;
		d.a.x = d.t.x / Z;
		d.a.y = d.t.y / Z;
		if (check_hit(data, &d, ray, door) == 1)
			return (d.dis);
		d.first_inter.x += d.stp.x;
		d.first_inter.y += d.stp.y;
	}
}

void get_v_inter(t_data *data, t_dis *d)
{	
	d->ply.x = data->player.x - data->map_x;
	d->ply.y = data->player.y - data->map_y;
	d->first_inter.x = floor(d->ply.x / Z) * Z;
	if (facing_right(d->beta))
		d->first_inter.x += Z;
	d->first_inter.y = d->ply.y + \
	((d->first_inter.x - d->ply.x) * tan(d->beta));
	d->stp.x = Z;
	if (!facing_right(d->beta))
		d->stp.x *= -1;
	d->stp.y = Z * tan(d->beta);
	if ((!facing_down(d->beta) && d->stp.y > 0) || \
	(facing_down(d->beta) && d->stp.y < 0))
		d->stp.y *= -1;
}

double	v_distance(t_data *data, double beta,t_ray *ray)
{
	t_dis	d;
	t_door	door;

	d.beta = beta;
	d.h_or_v = 2;
	get_v_inter(data, &d);
	while (1)
	{
		door.h_or_v = 0;
		door.dis_door = 0;
		door.x_door = 0;
		door.y_door = 0;
		d.t.x = d.first_inter.x;
		d.t.y = d.first_inter.y;
		if (!facing_right(beta))
			d.t.x -= 1;
		d.a.x = d.t.x / Z;
		d.a.y = d.t.y / Z;
		if (check_hit(data, &d, ray, door) == 1)
			return (d.dis);
		d.first_inter.x += d.stp.x;
		d.first_inter.y += d.stp.y;
	}
}