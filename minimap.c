/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:22:07 by zait-sli          #+#    #+#             */
/*   Updated: 2022/10/02 23:50:00 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int get_color(char c)
{
	int color = 0;
	
	if (c == '0' || check_player(c))
	{
		color = 16777215;
	}
	else if (c == '1')
		color = 35184;
	return (color);
}

int run(t_data *data)
{
	if (data->player.walkdirection != 0)
		draw(data);
	else if (data->player.turndirection != 0)
		draw(data);
	return(0);
}


// void    draw_walls(t_data *data)
// {
// int i = 0;
// int j;
// int txtr_offx;
// int txtr_offy;
// int distfromtop;
// double rad = (FOV) * (M_PI / 180);
// double distance_to_proj = (W_width / 2)  / tan(rad / 2);

// while(i < rays)
// {
// 	if(data->r[i].h_or_v == 2)
// 		txtr_offx = (int)data->r[i].y % (Z);
// 	else if (data->r[i].h_or_v == 1)
// 		txtr_offx = (int)data->r[i].x % (Z);
// 	double per_distance = data->r[i].distance * cos(data->r[i].alpha - data->player.teta);
// 	double proj_wall_height = (Z / per_distance) * distance_to_proj;
// 	int temp = (int)proj_wall_height;
// 	int wall_top_pixel = (W_height / 2) - (temp / 2);
// 	if (wall_top_pixel < 0)
// 		wall_top_pixel = 0;
// 	int wall_bottom_pixel = (W_height / 2) + (temp / 2);
// 	if (wall_bottom_pixel > W_height)
// 		wall_bottom_pixel = W_height;
// 	j = wall_top_pixel;
// 	while(j < wall_bottom_pixel)
// 	{
// 		distfromtop = j + (temp / 2) - (W_height / 2);
// 		txtr_offy = distfromtop * ((double)data->texture.height / proj_wall_height);
// 		my_mlx_pixel_put(&data->window, i, j, data->texture.tab[data->texture.width *(txtr_offy + txtr_offx)]);
// 		// my_mlx_pixel_put(&data->window, i, j, 0);
// 		j++;
// 	}
// 	i++;
// }
// }

t_texture which_texture(t_data *data,int i)
{
	if (data->r[i].h_or_v == 1)
	{
		if (normalize(data->r[i].alpha) >= M_PI && normalize(data->r[i].alpha) < 2 * M_PI)
			return(data->txtr.north);
		else
			return(data->txtr.south);
	}
	else
	{
		if (normalize(data->r[i].alpha) >= (M_PI / 2) && normalize(data->r[i].alpha) < 3 * (M_PI / 2))
			return(data->txtr.east);
		else
			return(data->txtr.west);
	}	
}

void    draw_walls(t_data *data)
{
	int i = 0;
	int j;
	t_point txtr_off;
	double x;
	double a;
	double rad = (FOV) * (M_PI / 180);
	t_texture tx;

	while(i < rays)
	{
		tx = which_texture(data,i);
		if(data->r[i].h_or_v == 2)
			txtr_off.x = (data->r[i].y - data->map_y) / Z;
		else
			txtr_off.x = (data->r[i].x - data->map_x) / Z;
		txtr_off.x = txtr_off.x - floor(txtr_off.x);
		txtr_off.x *= tx.width;
		double per_distance = data->r[i].distance * cos(data->r[i].alpha - data->player.teta);
		double distance_to_proj = (W_width / 2)  / tan(rad / 2);
		double proj_wall_height = (Z / per_distance) * distance_to_proj;
		a = (int)proj_wall_height;
		if (proj_wall_height > W_height)
			proj_wall_height =  W_height;
		int wall_top_pixel = (W_height / 2) - ((int)proj_wall_height / 2);
		int wall_bottom_pixel = (W_height / 2) + ((int)proj_wall_height / 2);
		x =  (a / 2) - (W_height / 2);
		j = wall_top_pixel;
		while(j < wall_bottom_pixel)
		{
			txtr_off.y = (j + x) * (tx.height / (a));
			txtr_off.y = floor(txtr_off.y);
			txtr_off.y *= tx.width;
			my_mlx_pixel_put(&data->window, i, j, tx.tab[(int)txtr_off.x + (int)txtr_off.y]);
			j++;
		}
		i++;
	}
}

int facing_down(double beta)
{
	if (beta > 0 && beta < M_PI)
	{
		return(1);
	}
	return(0);
}

int facing_right(double beta)
{
	if (beta < M_PI / 2 || beta > 1.5 * M_PI)
	{
		return(1);
	}
	return(0);
}

double findMod(double a, double b)
{
	double mod;
	if (a < 0)
		mod = -a;
	else
		mod =  a;
	if (b < 0)
		b = -b;
 
	 
	while (mod >= b)
		mod = mod - b;
	if (a < 0)
		return -mod;
 
	return mod;
}

double normalize(double teta)
{
	teta = findMod(teta, 2 * M_PI);
	if (teta < 0)
		 teta += (M_PI * 2);
	return(teta);
}

void	draw_rays(t_segment *seg, t_data *data)
{
	int i = 0;
	seg->x0 = data->player.x;
	seg->y0 = data->player.y;
	while(i < rays)
	{
		seg->x1 = data->r[i].x;
		seg->y1 = data->r[i].y;
		DDA2(data, *seg,0xFFFFFFF);
		i++;
	}
}

void move_player(t_data *data)
{
	t_point p;
	t_point t;
	
	data->player.teta = normalize(data->player.teta);
	data->player.teta += data->player.turndirection * rotationspeed;
	if(data->player.sides == 0 && (data->player.walkdirection != 0))
	{
		p.x += (cos(data->player.teta) * data->player.walkdirection * step);
		p.y += (sin(data->player.teta) * data->player.walkdirection * step);
	}
	if(data->player.sides == 1 && (data->player.walkdirection != 0))
	{
		p.x -= (sin(data->player.teta) * data->player.walkdirection * step);
		p.y += (cos(data->player.teta) * data->player.walkdirection * step);
	}
	t.x = (data->player.x - data->map_x + p.x) / Z;
	t.y = (data->player.y - data->map_y + p.y) / Z;
	if (data->map[(int)t.y][(int)t.x] == '0' || check_player(data->map[(int)t.y][(int)t.x]))
	{
		data->player.x += p.x;
		data->player.y += p.y;
	}
}