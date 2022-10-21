/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:22:07 by zait-sli          #+#    #+#             */
/*   Updated: 2022/10/20 23:36:38 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_color(char c)
{
	int	color;

	color = 0;
	if (c == '0' || check_player(c))
	{
		color = 16777215;
	}
	else if (c == '1')
		color = 35184;
	return (color);
}

int	run(t_data *data)
{
	if (data->player.walkdirection != 0)
		draw(data);
	else if (data->player.turndirection != 0)
		draw(data);
	return (0);
}

t_texture	which_texture(t_data *data, int i)
{
	if (data->r[i].h_or_v == 1)
	{
		if (normalize(data->r[i].alpha) >= M_PI
			&& normalize(data->r[i].alpha) < 2 * M_PI)
			return (data->txtr.north);
		else
			return (data->txtr.south);
	}
	else
	{
		if (normalize(data->r[i].alpha) >= (M_PI / 2)
			&& normalize(data->r[i].alpha) < 3 * (M_PI / 2))
			return (data->txtr.east);
		else
			return (data->txtr.west);
	}	
}

void	draw_walls_calc(t_data *data, t_dwvars	*dw)
{
	dw->txtr_off.x = dw->txtr_off.x - floor(dw->txtr_off.x);
	dw->txtr_off.x *= dw->tx.width;
	dw->per_distance = data->r[dw->i].distance * cos(data->r[dw->i].alpha
			- data->player.teta);
	dw->distance_to_proj = (W_WIDTH / 2) / tan(dw->rad / 2);
	dw->proj_wall_height = (Z / dw->per_distance) * dw->distance_to_proj;
	dw->a = (int)dw->proj_wall_height;
	if (dw->proj_wall_height > W_HEIGHT)
	dw->proj_wall_height = W_HEIGHT;
	dw->wall_top_pixel = (W_HEIGHT / 2) - ((int)dw->proj_wall_height / 2);
	dw->wall_bottom_pixel = (W_HEIGHT / 2) + ((int)dw->proj_wall_height / 2);
	dw->x = (dw->a / 2) - (W_HEIGHT / 2);
	dw->j = dw->wall_top_pixel;
}

void	draw_walls(t_data *data)
{
	t_dwvars	dw;

	dw.rad = (FOV) * (M_PI / 180);
	dw.i = 0;
	while (dw.i < RAYS)
	{
		dw.tx = which_texture(data, dw.i);
		if (data->r[dw.i].h_or_v == 2)
			dw.txtr_off.x = (data->r[dw.i].y - data->map_y) / Z;
		else
			dw.txtr_off.x = (data->r[dw.i].x - data->map_x) / Z;
		draw_walls_calc(data, &dw);
		while (dw.j < dw.wall_bottom_pixel)
		{
			dw.txtr_off.y = (dw.j + dw.x) * (dw.tx.height / (dw.a));
			dw.txtr_off.y = floor(dw.txtr_off.y);
			dw.txtr_off.y *= dw.tx.width;
			my_mlx_pixel_put(&data->window, dw.i, dw.j,
				dw.tx.tab[(int)dw.txtr_off.x + (int)dw.txtr_off.y]);
			dw.j++;
		}
		dw.i++;
	}
}

int	facing_down(double beta)
{
	if (beta > 0 && beta < M_PI)
		return (1);
	return (0);
}

int	facing_right(double beta)
{
	if (beta < M_PI / 2 || beta > 1.5 * M_PI)
		return (1);
	return (0);
}

double	findmod(double a, double b)
{
	double	mod;

	if (a < 0)
		mod = -a;
	else
		mod = a;
	if (b < 0)
		b = -b;
	while (mod >= b)
		mod = mod - b;
	if (a < 0)
		return (-mod);
	return (mod);
}

double	normalize(double teta)
{
	teta = findmod(teta, 2 * M_PI);
	if (teta < 0)
		teta += (M_PI * 2);
	return (teta);
}

void	draw_rays(t_segment *seg, t_data *data)
{
	int	i;

	i = 0;
	seg->x0 = data->player.x;
	seg->y0 = data->player.y;
	while (i < RAYS)
	{
		seg->x1 = data->r[i].x;
		seg->y1 = data->r[i].y;
		dda2(data, *seg, 0xFFFFFFF);
		i++;
	}
}

void	move_player(t_data *data)
{
	t_point	p;
	t_point	t;

	data->player.teta = normalize(data->player.teta);
	data->player.teta += data->player.turndirection * ROTATIONSPEED;
	if (data->player.sides == 0 && (data->player.walkdirection != 0))
	{
		p.x += (cos(data->player.teta) * data->player.walkdirection * STEP);
		p.y += (sin(data->player.teta) * data->player.walkdirection * STEP);
	}
	if (data->player.sides == 1 && (data->player.walkdirection != 0))
	{
		p.x -= (sin(data->player.teta) * data->player.walkdirection * STEP);
		p.y += (cos(data->player.teta) * data->player.walkdirection * STEP);
	}
	t.x = (data->player.x - data->map_x + p.x) / Z;
	t.y = (data->player.y - data->map_y + p.y) / Z;
	if (data->map[(int)t.y][(int)t.x] == '0'
		|| check_player(data->map[(int)t.y][(int)t.x]))
	{
		data->player.x += p.x;
		data->player.y += p.y;
	}
}
