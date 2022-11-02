/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 20:34:30 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/01 01:04:34 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_door	*ft_new(t_door d)
{
	t_door	*new;

	new = malloc(sizeof(t_door));
	if (!new)
		return (NULL);
	*new  = d;
	new -> next = NULL;
	return (new);
}

void	ft_add_front(t_door **lst, t_door *new)
{
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	new -> next = *lst;
	*lst = new;
}

void get_h_inter(t_data *data, t_dis *d)
{	
	d->ply.x = data->player.x - data->map_x;
	d->ply.y = data->player.y - data->map_y;
	d->first_inter.y = floor(d->ply.y / Z) * Z;
	if (facing_down(d->beta))
		d->first_inter.y += Z;
	d->first_inter.x = d->ply.x + ((d->first_inter.y - d->ply.y) / tan(d->beta));
	d->stp.y = Z;
	if (!facing_down(d->beta))
		d->stp.y *= -1;
	d->stp.x = Z / tan(d->beta);
	if ((!facing_right(d->beta) && d->stp.x > 0) || (facing_right(d->beta) && d->stp.x < 0))
		d->stp.x *= -1;
}

int check_hit(t_data *data, t_dis *d,t_ray *ray, t_door door)
{
	if (d->a.y >= data->map_height || d->a.y < 0 || d->a.x > get_map_width(data,d->a.y) || d->a.x < 0)
	{	
		d->dis = sqrt(pow(d->first_inter.x - d->ply.x,2) + pow(d->first_inter.y - d->ply.y,2));
		return(1);
	}
	if (data->map[(int)d->a.y][(int)d->a.x] == '2')
	{
		ray->hit_door = 1;
		door.h_or_v = d->h_or_v;
		door.dis_door = sqrt(pow(d->first_inter.x - d->ply.x,2) + pow(d->first_inter.y - d->ply.y,2));
		door.x_door  = data->player.x + (cos(d->beta) * door.dis_door);
		door.y_door  = data->player.y + (sin(d->beta) * door.dis_door);
		ft_add_front(&ray->door,ft_new(door));
	}
	if (data->map[(int)d->a.y][(int)d->a.x] != '0' && data->map[(int)d->a.y][(int)d->a.x] != '2' && data->map[(int)d->a.y][(int)d->a.x] != '3' && !check_player(data->map[(int)d->a.y][(int)d->a.x]))
	{
		d->dis = sqrt(pow(d->first_inter.x - d->ply.x,2) + pow(d->first_inter.y - d->ply.y,2));
		return(1);
	}
	return(0);
}

double h_distance(t_data *data, double beta,t_ray *ray)
{
	t_dis d;
	t_door door;

	d.beta = beta;
	d.h_or_v = 1;
	get_h_inter(data,&d);
	while(1)
	{
		door.h_or_v = 0;
		door.dis_door = 0;
		door.x_door  = 0;
		door.y_door  = 0;
		d.t.x = d.first_inter.x;
		d.t.y = d.first_inter.y;
		if (!facing_down(d.beta))
				d.t.y -= 1;
		d.a.x = d.t.x / Z;
		d.a.y = d.t.y / Z;
		if (check_hit(data, &d,ray,door) == 1)
			return(d.dis);
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
	d->first_inter.y = d->ply.y + ((d->first_inter.x - d->ply.x) * tan(d->beta));
	d->stp.x = Z;
	if (!facing_right(d->beta))
		d->stp.x *= -1;
	d->stp.y = Z * tan(d->beta);
	if ((!facing_down(d->beta) && d->stp.y > 0) || (facing_down(d->beta) && d->stp.y < 0))
		d->stp.y *= -1;
}

double v_distance(t_data *data, double beta,t_ray *ray)
{
	t_dis d;
	t_door door;

	d.beta = beta;
	d.h_or_v = 2;
	get_v_inter(data, &d);
	while(1)
	{
		door.h_or_v = 0;
		door.dis_door = 0;
		door.x_door  = 0;
		door.y_door  = 0;
		d.t.x = d.first_inter.x;
		d.t.y = d.first_inter.y;
		if (!facing_right(beta))
			d.t.x -= 1;
		d.a.x = d.t.x / Z;
		d.a.y = d.t.y / Z;
		if (check_hit(data, &d,ray, door) == 1)
			return(d.dis);
		d.first_inter.x += d.stp.x;
		d.first_inter.y += d.stp.y;
	}
}

void best_distance(t_data *data, double beta, t_ray *ray)
{
	data->distance.distance = 0;
	double h;
	double v;
	
	beta = normalize(beta);
	h = h_distance(data, beta,ray);
	v = v_distance(data, beta,ray);
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
	double t = D_RAYS;
	t *= -1;

	int i = 0;
	data->r = malloc(sizeof(t_ray) * RAYS);

	while(i < RAYS)
	{
		data->r[i].hit_door = 0;
		data->r[i].door = calloc(sizeof(t_door),1);
		data->player.teta = normalize(data->player.teta);
		sigma = data->player.teta + (t);
		data->r[i].alpha = normalize(sigma);

		best_distance(data,sigma,&data->r[i]);
		data->r[i].x = data->player.x + (cos(sigma) * data->distance.distance);
		data->r[i].y = data->player.y + (sin(sigma) * data->distance.distance);
		data->r[i].distance = data->distance.distance;
		data->r[i].h_or_v = data->distance.h_or_v;
		
		// if (data->r[i].v_is_door || data->r[i].h_is_door)
		// {
			
		// 	if (data->r[i].v_is_door && data->r[i].h_is_door)
		// 	{
		// 		if (data->r[i].h_door < data->r[i].v_door)
		// 		{
		// 			door.h_or_v_door = 1;
		// 			door.dis_door  = data->r[i].h_door;
		// 		}
		// 		else 
		// 		{
		// 			door.h_or_v_door = 2;
		// 			door.dis_door  = data->r[i].v_door;
		// 		}
		// 	}
		// 	else if (data->r[i].h_is_door)
		// 	{
		// 		door.h_or_v_door = 1;
		// 		door.dis_door  = data->r[i].h_door;
		// 	}
		// 	else
		// 	{
		// 		door.h_or_v_door  = 2;
		// 		door.dis_door = data->r[i].v_door;
		// 	}
		// 	data->r[i].hit_door = 1;
		// 	door.x_door  = data->player.x + (cos(sigma) * door.dis_door);
		// 	door.y_door  = data->player.y + (sin(sigma) * door.dis_door);
		// 	// ft_add_front(&data->r[i].door,ft_new(door));
		// 	data->r[i].door = ft_new(door);
		// }
		// if (data->r[i].hit_door == 0)
		// 	free(data->r[i].door);

		i++;
		t += inc_rays;
	}
	// data->r = r;
}