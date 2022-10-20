/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:22:07 by zait-sli          #+#    #+#             */
/*   Updated: 2022/10/20 01:42:25 by zait-sli         ###   ########.fr       */
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
	else
		color = 0x808080;
	return (color);
}

int run(t_data *data)
{
	t_point p;
	p.y = data->player.y - data->map_y; 
	p.x = data->player.x - data->map_x; 

	// if (data->map[(int)((p.y - Z) / Z)][(int)((p.x) / Z)] != '2' && data->map[(int)((p.y + Z) / Z)][(int)((p.x) / Z)] != '2'\
	// && data->map[(int)((p.y) / Z)][(int)((p.x - Z) / Z)] != '2' && data->map[(int)((p.y) / Z)][(int)((p.x + Z) / Z)] != '2' && data->map[(int)((p.y) / Z)][(int)((p.x) / Z)] != '2')
	// {
	// 	data->open_door = 0;
	// }
	if (data->player.walkdirection != 0)
		draw(data);
	else if (data->player.turndirection != 0)
		draw(data);
	return(0);
}

t_texture which_texture(t_data *data,int i)
{
	t_point p;
	p.y = data->r[i].y - data->map_y; 
	p.x = data->r[i].x - data->map_x; 
	if (data->r[i].h_or_v == 1)
	{
		if (normalize(data->r[i].alpha) >= M_PI
			&& normalize(data->r[i].alpha) < 2 * M_PI)
		{
			if (data->map[(int)((p.y - STEP) / Z)][(int)((p.x) / Z)] == '2')
				return(data->txtr.door);
			else
				return(data->txtr.north);
		}
		else
		{			
			if (data->map[(int)((p.y + STEP) / Z)][(int)((p.x) / Z)] == '2')
				return(data->txtr.door);
			else
				return(data->txtr.south);
		}
	}
	else
	{
		if (normalize(data->r[i].alpha) >= (M_PI / 2)
			&& normalize(data->r[i].alpha) < 3 * (M_PI / 2))
		{
			if (data->map[(int)((p.y) / Z)][(int)((p.x - STEP) / Z)] == '2')
				return(data->txtr.door);
			else 
				return(data->txtr.east);
		}
		else
		{
			if (data->map[(int)((p.y) / Z)][(int)((p.x + STEP) / Z)] == '2')
				return(data->txtr.door);
			else 
				return(data->txtr.west);
		}
	}	
}
t_texture which_door_texture(t_data *data,int i)
{
	(void)i;
	return(data->txtr.door);
	// t_point p;
	// p.y = data->r[i].y - data->map_y; 
	// p.x = data->r[i].x - data->map_x; 
	// if (data->r[i].h_or_v == 1)
	// {
	// 	if (normalize(data->r[i].alpha) >= M_PI
	// 		&& normalize(data->r[i].alpha) < 2 * M_PI)
	// 	{
	// 		if (data->map[(int)((p.y - STEP) / Z)][(int)((p.x) / Z)] == '2')
	// 			return(data->txtr.door);
	// 		else
	// 			return(data->txtr.north);
	// 	}
	// 	else
	// 	{			
	// 		if (data->map[(int)((p.y + STEP) / Z)][(int)((p.x) / Z)] == '2')
	// 			return(data->txtr.door);
	// 		else
	// 			return(data->txtr.south);
	// 	}
	// }
	// else
	// {
	// 	if (normalize(data->r[i].alpha) >= (M_PI / 2)
	// 		&& normalize(data->r[i].alpha) < 3 * (M_PI / 2))
	// 	{
	// 		if (data->map[(int)((p.y) / Z)][(int)((p.x - STEP) / Z)] == '2')
	// 			return(data->txtr.door);
	// 		else 
	// 			return(data->txtr.east);
	// 	}
	// 	else
	// 	{
	// 		if (data->map[(int)((p.y) / Z)][(int)((p.x + STEP) / Z)] == '2')
	// 			return(data->txtr.door);
	// 		else 
	// 			return(data->txtr.west);
	// 	}
	// }	
}
void cast_door_ray(t_data *data, int i)
{
	int j;
	t_point txtr_off;
	double k;
	double a;
	double rad = (FOV) * (M_PI / 180);
	t_texture tx;

	tx = which_door_texture(data,i);
	// printf("%d\n\n", tx.tab[0]);
	if(data->r[i].h_or_v_door == 2)
		txtr_off.x = (data->r[i].y_door - data->map_y) / Z;
	else
		txtr_off.x = (data->r[i].x_door - data->map_x) / Z;
	txtr_off.x = txtr_off.x - floor(txtr_off.x);
	txtr_off.x *= tx.width;
	double per_distance = data->r[i].dis_door * cos(data->r[i].alpha - data->player.teta);
	double distance_to_proj = (W_WIDTH / 2)  / tan(rad / 2);
	double proj_wall_height = (Z / per_distance) * distance_to_proj;
	a = (int)proj_wall_height;
	if (proj_wall_height > W_HEIGHT)
		proj_wall_height =  W_HEIGHT;
	int wall_top_pixel = (W_HEIGHT / 2) - ((int)proj_wall_height / 2);
	int wall_bottom_pixel = (W_HEIGHT / 2) + ((int)proj_wall_height / 2);
	k =  (a / 2) - (W_HEIGHT / 2);
	j = wall_top_pixel;
	while(j < wall_bottom_pixel)
	{
		txtr_off.y = (j + k) * (tx.height / (a));
		txtr_off.y = floor(txtr_off.y);
		txtr_off.y *= tx.width;
		if (data->r[i].distance >= data->r[i].dis_door) 
			my_mlx_pixel_put(&data->window, i, j, 0xfffffff);
		j++;
	}
}
void    draw_walls(t_data *data)
{
	int i = 0;
	int j;
	t_point txtr_off;
	double k;
	double a;
	double rad = (FOV) * (M_PI / 180);
	t_texture tx;

	while(i < RAYS)
	{
		tx = which_texture(data,i);
		// printf("%d\n\n", tx.tab[0]);
		if(data->r[i].h_or_v == 2)
			txtr_off.x = (data->r[i].y - data->map_y) / Z;
		else
			txtr_off.x = (data->r[i].x - data->map_x) / Z;
		txtr_off.x = txtr_off.x - floor(txtr_off.x);
		txtr_off.x *= tx.width;
		double per_distance = data->r[i].distance * cos(data->r[i].alpha - data->player.teta);
		double distance_to_proj = (W_WIDTH / 2)  / tan(rad / 2);
		double proj_wall_height = (Z / per_distance) * distance_to_proj;
		a = (int)proj_wall_height;
		if (proj_wall_height > W_HEIGHT)
			proj_wall_height =  W_HEIGHT;
		int wall_top_pixel = (W_HEIGHT / 2) - ((int)proj_wall_height / 2);
		int wall_bottom_pixel = (W_HEIGHT / 2) + ((int)proj_wall_height / 2);
		k =  (a / 2) - (W_HEIGHT / 2);
		j = wall_top_pixel;
		while(j < wall_bottom_pixel)
		{
			txtr_off.y = (j + k) * (tx.height / (a));
			txtr_off.y = floor(txtr_off.y);
			txtr_off.y *= tx.width;
			my_mlx_pixel_put(&data->window, i, j, tx.tab[(int)txtr_off.x + (int)txtr_off.y]);
			j++;
		}
		if (data->r[i].hit_door == 1)
			cast_door_ray(data, i);
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
	while(i < RAYS)
	{
		seg->x1 = data->r[i].x;
		seg->y1 = data->r[i].y;
		dda2(data, *seg,0xFFFFFFF);
		i++;
	}
}

int door(t_data *data, char c)
{
	if (c == '2' && data->open_door == 1)
		return(1);
	else
		return(0);
}

void move_player(t_data *data)
{
	t_point p;
	t_point t;
	
	data->player.teta = normalize(data->player.teta);
	data->player.teta += data->player.turndirection * ROTATIONSPEED;
	if(data->player.sides == 0 && (data->player.walkdirection != 0))
	{
		p.x += (cos(data->player.teta) * data->player.walkdirection * STEP);
		p.y += (sin(data->player.teta) * data->player.walkdirection * STEP);
	}
	if(data->player.sides == 1 && (data->player.walkdirection != 0))
	{
		p.x -= (sin(data->player.teta) * data->player.walkdirection * STEP);
		p.y += (cos(data->player.teta) * data->player.walkdirection * STEP);
	}
	t.x = (data->player.x - data->map_x + p.x) / Z;
	t.y = (data->player.y - data->map_y + p.y) / Z;
	if (data->map[(int)t.y][(int)t.x] == '0' || data->map[(int)t.y][(int)t.x] == '2' || check_player(data->map[(int)t.y][(int)t.x]))
	{
		data->player.x += p.x;
		data->player.y += p.y;
	}
}