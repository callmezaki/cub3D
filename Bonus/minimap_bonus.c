/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:22:07 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/07 19:48:50 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	run(t_data *data)
{
	draw(data);
	mlx_hook(data->window.mlx_win, 2, 1L << 0, key_press, data);
	mlx_hook(data->window.mlx_win, 3, 0L, key_release, data);
	mlx_hook(data->window.mlx_win, 17, 0, you_quit, NULL);
	mlx_hook(data->window.mlx_win, 4, 0L, mouse_press, data);
	mlx_hook(data->window.mlx_win, 5, 0L, mouse_release, data);
	mlx_hook(data->window.mlx_win, 6, 0L, mouse_move, data);
	return (0);
}

int	door(t_data *data, char c)
{
	if (c == '2' && data->open_door == 1)
		return (1);
	else
		return (0);
}

int	check_coll(t_data *data)
{
	t_ray	ray;
	double	teta;

	ray.door = calloc(sizeof(t_door), 1);
	teta = data->player.teta;
	if (data->player.walkdirection == 1)
		teta = data->player.teta;
	else if (data->player.walkdirection == -1)
		teta = normalize(data->player.teta + M_PI);
	else if (data->player.sides == 1 && (data->player.teta < M_PI / 2 || \
	data->player.teta < 1.5 * M_PI))
		teta = normalize(data->player.teta + M_PI / 2);
	else if (data->player.sides == 1 && (data->player.teta >= 1.5 * M_PI && \
	data->player.teta <= M_PI / 2))
		teta = normalize(data->player.teta - M_PI / 2);
	best_distance(data, teta, &ray);
	free_list(ray.door);
	if (data->distance.distance <= 1)
		return (0);
	return (1);
}

void	make_step(t_point	*p, t_data *data)
{
	if (data->player.sides == 0 && (data->player.walkdirection != 0))
	{
		p->x += (cos(data->player.teta) * data->player.walkdirection * STEP);
		p->y += (sin(data->player.teta) * data->player.walkdirection * STEP);
	}
	if (data->player.sides == 1 && (data->player.walkdirection != 0))
	{
		p->x -= (sin(data->player.teta) * data->player.walkdirection * STEP);
		p->y += (cos(data->player.teta) * data->player.walkdirection * STEP);
	}
}

void	move_player(t_data *data)
{
	t_point	p;
	t_point	t;

	p.x = 0.0;
	p.y = 0.0;
	data->player.teta = normalize(data->player.teta);
	data->player.teta += data->player.turndirection * data->rotation_speed;
	make_step(&p, data);
	t.x = (data->player.x - data->map_x + p.x) / data->tile;
	t.y = (data->player.y - data->map_y + p.y) / data->tile;
	if ((data->map[(int)t.y][(int)t.x] == '0' || \
	data->map[(int)t.y][(int)t.x] == '2' || \
		check_player(data->map[(int)t.y][(int)t.x])) && check_coll(data))
	{
			data->player.x += p.x;
			data->player.y += p.y;
	}
}
