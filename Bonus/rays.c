/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 20:34:30 by zait-sli          #+#    #+#             */
/*   Updated: 2022/10/28 00:34:30 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// int ch_door(t_data *data ,char c)
// {
// 	if (c != '2')
// 		return(1);
// 	else
// 		return(0);
// }

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

double h_distance(t_data *data, double beta,t_ray *ray)
{
	t_point a; 
	t_point first_inter;
	t_point t;
	t_point stp;
	double h;
	t_door door;
	t_point ply;

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
	while(1)
	{
		door.h_or_v = 0;
		door.dis_door = 0;
		door.x_door  = 0;
		door.y_door  = 0;
		t.x = first_inter.x;
		t.y = first_inter.y;
		if (!facing_down(beta))
				t.y -= 1;
		
		a.x = t.x / Z;
		a.y = t.y / Z;
		if (a.y >= data->map_height || a.y < 0 || a.x > get_map_width(data,a.y) || a.x < 0)
		{	
			h = sqrt(pow(first_inter.x - ply.x,2) + pow(first_inter.y - ply.y,2));
			return(h);
		}
		if (data->map[(int)a.y][(int)a.x] == '2')
		{
			ray->hit_door = 1;
			door.h_or_v = 1;
			door.dis_door = sqrt(pow(first_inter.x - ply.x,2) + pow(first_inter.y - ply.y,2));
			door.x_door  = data->player.x + (cos(beta) * door.dis_door);
			door.y_door  = data->player.y + (sin(beta) * door.dis_door);
			ft_add_front(&ray->door,ft_new(door));
		}
		if (data->map[(int)a.y][(int)a.x] != '0' && data->map[(int)a.y][(int)a.x] != '2' && data->map[(int)a.y][(int)a.x] != '3' && !check_player(data->map[(int)a.y][(int)a.x]))
		{
			h = sqrt(pow(first_inter.x - ply.x,2) + pow(first_inter.y - ply.y,2));
			return(h);
		}
		first_inter.x += stp.x;
		first_inter.y += stp.y;
	}
}

double v_distance(t_data *data, double beta,t_ray *ray)
{
	t_point a; 
	t_point first_inter;
	t_point t;
	t_point stp;
	double h;
	t_point ply;
	// int done = 0;
	t_door door;

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
	while(1)
	{
		door.h_or_v = 0;
		door.dis_door = 0;
		door.x_door  = 0;
		door.y_door  = 0;
		t.x = first_inter.x;
		t.y = first_inter.y;
		if (!facing_right(beta))
			t.x -= 1;
		
		a.x = t.x / Z;
		a.y = t.y / Z;
		if (a.y >= data->map_height || a.y < 0 || a.x > get_map_width(data,a.y) || a.x < 0)
		{	
			h = sqrt(pow(first_inter.x - ply.x,2) + pow(first_inter.y - ply.y,2));
			return(h);
		}
		if (data->map[(int)a.y][(int)a.x] == '2')
		{
			ray->hit_door = 1;
			door.h_or_v = 2;
			door.dis_door = sqrt(pow(first_inter.x - ply.x,2) + pow(first_inter.y - ply.y,2));
			door.x_door  = data->player.x + (cos(beta) * door.dis_door);
			door.y_door  = data->player.y + (sin(beta) * door.dis_door);
			ft_add_front(&ray->door,ft_new(door));
		}	
		if (data->map[(int)a.y][(int)a.x] != '0'  && data->map[(int)a.y][(int)a.x] != '2' && data->map[(int)a.y][(int)a.x] != '3'&& !check_player(data->map[(int)a.y][(int)a.x]))
		{
			h = sqrt(pow(first_inter.x - ply.x,2) + pow(first_inter.y - ply.y,2));
			return(h);
		}
		first_inter.x += stp.x;
		first_inter.y += stp.y;
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
		i++;
		t += inc_rays;
	}
	// data->r = r;
}