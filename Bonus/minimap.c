/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:22:07 by zait-sli          #+#    #+#             */
/*   Updated: 2022/10/30 18:18:34 by zait-sli         ###   ########.fr       */
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
		color = 0xB7CECE;
	else if (c == '2')
		color = 0x011627;
	else
		color = 0x808080;
	return (color);
}

int run(t_data *data)
{
	draw(data);
	mlx_hook(data->window.mlx_win, 2, 1L << 0, key_press, data);
	mlx_hook(data->window.mlx_win, 3, 0L, key_release, data);
	mlx_hook(data->window.mlx_win, 17, 0, you_quit, NULL);
	mlx_hook(data->window.mlx_win, 4, 0L, mouse_press, data);
	mlx_hook(data->window.mlx_win, 5, 0L, mouse_release, data);
	mlx_hook(data->window.mlx_win, 6, 0L, mouse_move, data);
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
			return(data->txtr.north);
		}
		else
		{			
			return(data->txtr.south);
		}
	}
	else
	{
		if (normalize(data->r[i].alpha) >= (M_PI / 2)
			&& normalize(data->r[i].alpha) < 3 * (M_PI / 2))
		{
			return(data->txtr.east);
		}
		else
		{
			return(data->txtr.west);
		}
	}	
}
t_texture which_door_texture(t_data *data, t_door *door)
{
	if (door->dis_door <= 35 && door->dis_door > 30)
	{
		return(data->txtr.d_f1);
	}
	else if (door->dis_door <= 30 && door->dis_door > 25)
	{
		return(data->txtr.d_f2);
	}
	else if (door->dis_door <= 25 && door->dis_door > 20)
	{
		return(data->txtr.d_f3);
	}	
	else if (door->dis_door <= 20 && door->dis_door > 15)
	{
		return(data->txtr.d_f4);
	}
	else if (door->dis_door <= 15 && door->dis_door > 10)
	{
		return(data->txtr.d_f5);
	}
	else if (door->dis_door <= 10)
	{
		return(data->txtr.d_f6);
	}
	else
		return(data->txtr.d_f0);
}

void cast_door_ray(t_door *door,t_data *data,int i)
{
	int j;
	t_point txtr_off;
	double k;
	double a;
	double rad = (FOV) * (M_PI / 180);
	t_texture tx;
	double proj_wall_height = 0;
	

	tx = which_door_texture(data,door);
	if(door->h_or_v == 2)
		txtr_off.x = (door->y_door - data->map_y) / Z;
	else
		txtr_off.x = (door->x_door - data->map_x) / Z;
	txtr_off.x = txtr_off.x - floor(txtr_off.x);
	txtr_off.x *= tx.width;
	door->dis_door = door->dis_door * cos(data->r[i].alpha - data->player.teta);
	if (data->r[i].distance <= door->dis_door)
		return ;
	double distance_to_proj = (W_WIDTH / 2)  / tan(rad / 2);
	proj_wall_height = (Z / door->dis_door) * distance_to_proj;
	a = proj_wall_height;
	if (proj_wall_height > W_HEIGHT)
		proj_wall_height =  W_HEIGHT;
	int wall_top_pixel = (W_HEIGHT / 2) - ((int)proj_wall_height / 2);
	int wall_bottom_pixel = (W_HEIGHT / 2) + ((int)proj_wall_height / 2);
	if (wall_bottom_pixel > W_HEIGHT)
		wall_bottom_pixel = W_HEIGHT;
	k =  ((int)a / 2) - (W_HEIGHT / 2);
	j = wall_top_pixel;
	while(j < wall_bottom_pixel)
	{
		txtr_off.y = (j + k) * (tx.height / a);
		txtr_off.y = floor(txtr_off.y);
		txtr_off.y *= tx.width;
		if (tx.tab[(int)txtr_off.x + (int)txtr_off.y] != 16711935 && ((int)txtr_off.x + (int)txtr_off.y) < (tx.height * tx.width))
		{
			my_mlx_pixel_put(&data->window, i, j,tx.tab[(int)txtr_off.x + (int)txtr_off.y]);
		}
		j++;
	}
}

void free_list(t_door *door)
{
	t_door *d;
	
	while(door->next)
	{
		d = door;
		door = door->next;
		free(d);
	}
}

int return_firstx(t_data *data, t_sprite sp)
{
	t_point t;
	double rad = (FOV) * (M_PI / 180);
	double distance_to_proj = (W_WIDTH / 2)  / tan(rad / 2);
	double sprite_width = (Z / sp.distance) * distance_to_proj;
	t.y =  sp.y - data->player.y;
	t.x =  sp.x - data->player.x;
	sp.angle = normalize(atan2(t.y, t.x) - data->player.teta);
	double sprite_sc_posX = tan(sp.angle) * distance_to_proj;
	double sprite_leftX = (W_WIDTH / 2) + sprite_sc_posX  - (sprite_width / 2);
	return((int)sprite_leftX);
}

void draw_doors(t_data *data)
{
	int i = 0;
	int x = 0;
	t_door *door;
	while(i < RAYS)
	{
		if (data->r[i].hit_door == 1)
		{
			door = data->r[i].door;
			while(door->next)
			{
				x = 0;
				while (x < data->sp)
				{
					// printf("x = %d, i = %d\n",return_firstx(data, data->sprites[x]),i);
					if (return_firstx(data, data->sprites[x]) == i && data->sprites[x].distance > door->dis_door && data->sprites[x].drown == 0)
					{
						// printf("sp_dis = %f > d_dis = %f,\n",data->sprites[x].angle ,data->r[i].alpha);
						draw_sprite(data, x);
					}
					x++;
				}
				cast_door_ray(door, data,i);
				door = door->next;
			}
			free_list(data->r[i].door);
		}
		i++;
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
		if(data->r[i].h_or_v == 2)
			txtr_off.x = (data->r[i].y - data->map_y) / Z;
		else
			txtr_off.x = (data->r[i].x - data->map_x) / Z;
		txtr_off.x = txtr_off.x - floor(txtr_off.x);
		txtr_off.x *= tx.width;
		double distance_to_proj = (W_WIDTH / 2)  / tan(rad / 2);
		data->r[i].distance = data->r[i].distance * cos(data->r[i].alpha - data->player.teta);
		double proj_wall_height = (Z / data->r[i].distance) * distance_to_proj;
		a = (int)proj_wall_height;
		if (proj_wall_height > W_HEIGHT)
			proj_wall_height =  W_HEIGHT;
		int wall_top_pixel = (W_HEIGHT / 2) - ((int)proj_wall_height / 2);
		int wall_bottom_pixel = (W_HEIGHT / 2) + ((int)proj_wall_height / 2);
		k =  ((int)a / 2) - (W_HEIGHT / 2);
		j = wall_top_pixel;
		while(j < wall_bottom_pixel)
		{
			txtr_off.y = (j + k) * (tx.height / a);
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
	
	// int i = 0;
	// seg->x0 = data->player.x;
	// seg->y0 = data->player.y;
		// while(i < RAYS)
		// {

			// seg->x1 = data->r[i].x;
			// seg->y1 = data->r[i].y;
			seg->x0 = data->player.x;
			seg->y0 = data->player.y;
			seg->x1 = data->r[RAYS / 2].x;
			seg->y1 = data->r[RAYS / 2].y;
			dda2(data, *seg,0);
		// 	i++;
		// }
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
	
	p.x = 0.0;
	p.y = 0.0;
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
		if(data->map[(int)t.y][(int)t.x] == '0' && data->map[(int)t.y][(int)t.x - 1] == '1'
			&& data->map[(int)t.y + 1][(int)t.x] == '1' && data->map[(int)t.y + 1][(int)t.x - 1] == '0');
		else
		{
			data->player.x += p.x;
			data->player.y += p.y;
		}
	}
}