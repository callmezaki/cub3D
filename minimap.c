/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:22:07 by zait-sli          #+#    #+#             */
/*   Updated: 2022/09/25 21:27:59 by sgmira           ###   ########.fr       */
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
		color = 8421504;
	return (color);
}

int rgb_to_dec(t_color color)
{
	int dec;

	dec = (color.R << 16) + (color.G << 8) + color.B;
	return(dec);
}

void	draw_background(t_data *data)
{
	int x;
	int y;
	int c;

	x = 0;
	y = 0;
	c = rgb_to_dec(data->C);
	while(y < W_height)
	{
		x = 0;
		if(y == W_height / 2)
			c = rgb_to_dec(data->F);
		while(x < W_width)
		{
			my_mlx_pixel_put(&data->window, x, y, c);
			x++;
		}
		y++;
	}
	
}

int draw(t_data *data)
{
	mlx_clear_window(data->window.mlx, data->window.mlx_win);
	data->window.img = mlx_new_image(data->window.mlx, W_width, W_height);
	data->window.addr = mlx_get_data_addr(data->window.img, &data->window.bits_per_pixel, &data->window.line_length,
								&data->window.endian);
	draw_background(data);
	claculate_rays(data);
	draw_walls(data);
	draw_minimap(data);
	draw_player(data);
	mlx_put_image_to_window(data->window.mlx, data->window.mlx_win, data->window.img, 0, 0);
	mlx_destroy_image(data->window.mlx, data->window.img);
	return(0);
}
int draw_minimap(t_data *data)
{
	t_block block;
	int i = 0;
	int j = 0;
	

	block.x0 = 0;
	block.y0 = -Z;
	block.x1 = 0;
	block.y1 = 0;
	while(data->map[i])
	{
		block.x0 = 0;
		block.x1 = block.x0 + Z;
		block.y0 += Z;
		block.y1 = block.y0 + Z;
		j = 0;
		while(data->map[i][j])
		{
			if (data->map[i][j] == ' ');
			else
			{
				block.color = get_color(data->map[i][j]);
				ft_block(&data->window, block);
			}
			block.x0 = block.x1;
			block.x1 += Z;
			j++;
		}
		i++;
	}
	return(0);
}

void	draw_walls(t_data *data)
{
	int i = 0;
	t_segment seg;

	while(i < rays)
	{
		double per_distance = data->r[i].distance * cos(data->r[i].alpha - data->player.teta);
		double distance_to_proj = rays / tan(FOV / 2);
		double proj_wall_height = (80 / per_distance) * distance_to_proj;
		if (proj_wall_height > W_height)
			proj_wall_height = W_height;
		int wall_top_pixel = (W_height / 2) - (proj_wall_height / 2);
		int wall_bottom_pixel = (W_height / 2) + (proj_wall_height / 2);
		seg.x0 = i;
		seg.y0 = wall_top_pixel;
		seg.x1 = i;
		seg.y1 = wall_bottom_pixel;
		DDA(data, seg,0x808080);
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
    // Handling negative values
    if (a < 0)
        mod = -a;
    else
        mod =  a;
    if (b < 0)
        b = -b;
 
    // Finding mod by repeated subtraction
     
    while (mod >= b)
        mod = mod - b;
 
    // Sign of result typically depends
    // on sign of a.
    if (a < 0)
        return -mod;
 
    return mod;
}

double normalize(double teta)
{
	// teta = teta % (2 * M_PI);
	teta = findMod(teta, 2 * M_PI);
	if (teta < 0)
		 teta += (M_PI * 2);

	return(teta);
}

double h_distance(t_data *data, double beta)
{
	t_point a; 
	t_point First_inter;
	t_point t;
	t_point stp;
	double h;
	
	First_inter.y = floor(data->player.y / Z) * Z;
	if (facing_down(beta))
		First_inter.y += Z;
	First_inter.x = data->player.x + ((First_inter.y - data->player.y) / tan(beta));
	stp.y = Z;
	if (!facing_down(beta))
		stp.y *= -1;
	stp.x = Z / tan(beta);
	if ((!facing_right(beta) && stp.x > 0) || (facing_right(beta) && stp.x < 0))
		stp.x *= -1;
	while(1)
	{
		t.x = First_inter.x;
		t.y = First_inter.y;
		if (!facing_down(beta))
			t.y -= 1;
		a.x = t.x / Z;
		a.y = t.y / Z;
		if (a.y >= data->map_height || a.y < 0 || a.x > get_map_width(data,a.y) || a.x < 0)
		{			
			h = sqrt(pow(First_inter.x - data->player.x,2) + pow(First_inter.y - data->player.y,2));
			return(h);
		}
		if (data->map[(int)a.y][(int)a.x] != '0' && !check_player(data->map[(int)a.y][(int)a.x]))
		{
			h = sqrt(pow(First_inter.x - data->player.x,2) + pow(First_inter.y - data->player.y,2));
			return(h);
		}
		First_inter.x += stp.x;
		First_inter.y += stp.y;
	}
}

double v_distance(t_data *data, double beta)
{
	t_point a; 
	t_point First_inter;
	t_point t;
	t_point stp;
	double h;
	
	First_inter.x = floor(data->player.x / Z) * Z;
	if (facing_right(beta))
		First_inter.x += Z;
	First_inter.y = data->player.y + ((First_inter.x - data->player.x) * tan(beta));
	stp.x = Z;
	if (!facing_right(beta))
		stp.x *= -1;
	stp.y = Z * tan(beta);
	if ((!facing_down(beta) && stp.y > 0) || (facing_down(beta) && stp.y < 0))
		stp.y *= -1;
	while(1)
	{
		t.x = First_inter.x;
		t.y = First_inter.y;
		if (!facing_right(beta))
			t.x -= 1;
		a.x = t.x / Z;
		a.y = t.y / Z;
		if (a.y >= data->map_height || a.y < 0 || a.x > get_map_width(data,a.y) || a.x < 0)
		{			
			h = sqrt(pow(First_inter.x - data->player.x,2) + pow(First_inter.y - data->player.y,2));
			return(h);
		}
		if (data->map[(int)a.y][(int)a.x] != '0' && !check_player(data->map[(int)a.y][(int)a.x]))
		{
			h = sqrt(pow(First_inter.x - data->player.x,2) + pow(First_inter.y - data->player.y,2));
			return(h);
		}
		First_inter.x += stp.x;
		First_inter.y += stp.y;
	}
}

double best_distance(t_data *data, double beta)
{
	double distance = 0;
	double h;
	double v;
	
	beta = normalize(beta);
	v = v_distance(data, beta);
	h = h_distance(data, beta);
	if (h < v)
		distance = h;
	else  
		distance = v;
	return(distance);
}

void	claculate_rays(t_data *data)
{
	double distance = 0;
	double sigma;
	double t = D_rays;
	t *= -1;

	int i = 0;
	t_ray* r;
	r = malloc(sizeof(t_ray) * rays);

	while(i < rays)
	{
		sigma = data->player.teta + (t);
		distance = best_distance(data,sigma);
		r[i].x  = data->player.x + (cos(sigma) * distance);
		r[i].y = data->player.y + (sin(sigma) * distance);
		r[i].distance = distance;
		r[i].alpha = sigma;
		i++;
		t += inc_rays;
	}
	data->r = r;
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
		DDA(data, *seg,0x7FB3D5);
		i++;
	}
}

void draw_player(t_data *data)
{
	t_segment seg;
	
	data->player.teta += data->player.turndirection * data->player.rotationspeed;
	data->player.x += (cos(data->player.teta) * data->player.walkdirection * data->player.movespeed);
	data->player.y += (sin(data->player.teta) * data->player.walkdirection * data->player.movespeed);
	double x = (data->player.x) / Z;
	double y = (data->player.y) / Z ;
	if (data->map[(int)y][(int)x] != '0' && !check_player(data->map[(int)y][(int)x]))
	{
		data->player.x -= (cos(data->player.teta) * data->player.walkdirection * data->player.movespeed);
		data->player.y -= (sin(data->player.teta) * data->player.walkdirection * data->player.movespeed);
	}
	draw_rays(&seg, data);
}