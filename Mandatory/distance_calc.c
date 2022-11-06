/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_calc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 00:06:27 by sgmira            #+#    #+#             */
/*   Updated: 2022/11/06 23:42:28 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	h_distance_calc(t_data *data, double beta)
{
	data->ply.x = data->player.x - data->map_x;
	data->ply.y = data->player.y - data->map_y;
	data->first_inter.y = floor(data->ply.y / data->tile) * data->tile;
	if (facing_down(beta))
		data->first_inter.y += data->tile;
	data->first_inter.x = data->ply.x
		+ ((data->first_inter.y - data->ply.y) / tan(beta));
	data->stp.y = data->tile;
	if (!facing_down(beta))
		data->stp.y *= -1;
	data->stp.x = data->tile / tan(beta);
	if ((!facing_right(beta) && data->stp.x > 0)
		|| (facing_right(beta) && data->stp.x < 0))
		data->stp.x *= -1;
}

void	h_distance_calc2(t_data *data, double beta)
{
	data->t.x = data->first_inter.x;
	data->t.y = data->first_inter.y;
	if (!facing_down(beta))
		data->t.y -= 1;
	data->a.x = data->t.x / data->tile;
	data->a.y = data->t.y / data->tile;
}

double	h_distance(t_data *data, double beta)
{
	double	h;

	h_distance_calc(data, beta);
	while (1)
	{
		h_distance_calc2(data, beta);
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

void	v_distance_calc(t_data *data, double beta)
{
	data->ply.x = data->player.x - data->map_x;
	data->ply.y = data->player.y - data->map_y;
	data->first_inter.x = floor(data->ply.x / data->tile) * data->tile;
	if (facing_right(beta))
		data->first_inter.x += data->tile;
	data->first_inter.y = data->ply.y
		+ ((data->first_inter.x - data->ply.x) * tan(beta));
	data->stp.x = data->tile;
	if (!facing_right(beta))
		data->stp.x *= -1;
	data->stp.y = data->tile * tan(beta);
	if ((!facing_down(beta) && data->stp.y > 0)
		|| (facing_down(beta) && data->stp.y < 0))
		data->stp.y *= -1;
}

void	v_distance_calc2(t_data *data, double beta)
{
	data->t.x = data->first_inter.x;
	data->t.y = data->first_inter.y;
	if (!facing_right(beta))
		data->t.x -= 1;
	data->a.x = data->t.x / data->tile;
	data->a.y = data->t.y / data->tile;
}
