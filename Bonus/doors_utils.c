/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 03:37:12 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/06 04:59:06 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_list(t_door *door)
{
	t_door	*d;

	while (door->next)
	{
		d = door;
		door = door->next;
		free(d);
	}
	free(door);
}

int	return_firstx(t_data *data, t_sprite sp)
{
	t_dwsprite	s;

	s.rad = (FOV) * (M_PI / 180);
	s.distance_to_proj = (W_WIDTH / 2) / tan(s.rad / 2);
	s.sp_width = (Z / sp.distance) * s.distance_to_proj;
	s.t.y = sp.y - data->player.y;
	s.t.x = sp.x - data->player.x;
	sp.angle = normalize(atan2(s.t.y, s.t.x) - data->player.teta);
	s.sp_sc_posx = tan(sp.angle) * s.distance_to_proj;
	s.sp_leftx = (W_WIDTH / 2) + s.sp_sc_posx - (s.sp_width / 2);
	return ((int)s.sp_leftx);
}

void	draw_doors(t_data *data)
{
	int		i;
	int		x;
	t_door	*door;

	i = -1;
	while (++i < RAYS)
	{
		if (data->r[i].hit_door == 1)
		{
			door = data->r[i].door;
			while (door->next)
			{
				x = -1;
				while (++x < data->sp)
				{
					if (return_firstx(data, data->sprites[x]) <= i && \
	data->sprites[x].distance > door->dis_door && data->sprites[x].drown == 0)
						draw_sprite(data, x);
				}
				cast_door_ray(door, data, i);
				door = door->next;
			}
		}
		free_list(data->r[i].door);
	}
}
