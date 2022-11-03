/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 20:34:30 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/03 19:31:27 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_door	*ft_new(t_door d)
{
	t_door	*new;

	new = malloc(sizeof(t_door));
	if (!new)
		return (NULL);
	*new = d;
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

void	best_distance(t_data *data, double beta, t_ray *ray)
{
	double	h;
	double	v;

	data->distance.distance = 0;
	beta = normalize(beta);
	h = h_distance(data, beta, ray);
	v = v_distance(data, beta, ray);
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

	t = D_RAYS * -1;
	data->r = malloc(sizeof(t_ray) * RAYS);
	i = 0;
	while (i < RAYS)
	{
		data->r[i].hit_door = 0;
		data->r[i].door = calloc(sizeof(t_door), 1);
		data->player.teta = normalize(data->player.teta);
		sigma = data->player.teta + (t);
		data->r[i].alpha = normalize(sigma);
		best_distance(data, sigma, &data->r[i]);
		data->r[i].x = data->player.x + (cos(sigma) * data->distance.distance);
		data->r[i].y = data->player.y + (sin(sigma) * data->distance.distance);
		data->r[i].distance = data->distance.distance;
		data->r[i].h_or_v = data->distance.h_or_v;
		i++;
		t += inc_rays;
	}
}
