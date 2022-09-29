/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:22:07 by zait-sli          #+#    #+#             */
/*   Updated: 2022/09/29 22:45:18 by sgmira           ###   ########.fr       */
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

// void	draw_walls(t_data *data)
// {
// 	int i = 0;
// 	t_segment seg;
// 	while(i < rays)
// 	{
// 		double per_distance = data->r[i].distance * cos(data->r[i].alpha - data->player.teta);
// 		double distance_to_proj = rays / tan(FOV / 2);
// 		double proj_wall_height = ((Z * 3) / per_distance) * distance_to_proj;
// 		if (proj_wall_height > W_height)
// 			proj_wall_height = W_height;
// 		int wall_top_pixel = (W_height / 2) - (proj_wall_height / 2);
// 		int wall_bottom_pixel = (W_height / 2) + (proj_wall_height / 2);
// 		seg.x0 = i;
// 		seg.y0 = wall_top_pixel;
// 		seg.x1 = i;
// 		seg.y1 = wall_bottom_pixel;
// 		DDA(data, seg,0x808080);
// 		i++;
// 	}
// }

void    draw_walls(t_data *data)
{
    int i = 0;
    int j;
	int txtr_offx;
	int txtr_offy;
	
    while(i < rays)
    {
		txtr_offx = (int)data->r[i].x % (Z * 3); 
        double per_distance = data->r[i].distance * cos(data->r[i].alpha - data->player.teta);
        double distance_to_proj = rays / tan(FOV / 2);
        double proj_wall_height = ((Z * 3) / per_distance) * distance_to_proj;
        if (proj_wall_height > W_height)
            proj_wall_height = W_height;
        int wall_top_pixel = (W_height / 2) - (proj_wall_height / 2);
        int wall_bottom_pixel = (W_height / 2) + (proj_wall_height / 2);
        j = wall_bottom_pixel;
        while(j < wall_top_pixel)
        {
			// printf("%f\n", proj_wall_height);
			txtr_offy = (j - wall_top_pixel) * ((double)16 / proj_wall_height);
            my_mlx_pixel_put(&data->window, i, j, data->texture.tab[(16 * txtr_offy) + txtr_offx]);
            // my_mlx_pixel_put(&data->window, i, j, 0);
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

double h_distance(t_data *data, double beta)
{
	t_point a; 
	t_point First_inter;
	t_point t;
	t_point stp;
	double h;
	t_point ply;

	ply.x = data->player.x - data->map_x;
	ply.y = data->player.y - data->map_y;
	First_inter.y = floor(ply.y / Z) * Z;
	if (facing_down(beta))
		First_inter.y += Z;
	First_inter.x = ply.x + ((First_inter.y - ply.y) / tan(beta));
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
			h = sqrt(pow(First_inter.x - ply.x,2) + pow(First_inter.y - ply.y,2));
			return(h);
		}
		if (data->map[(int)a.y][(int)a.x] != '0' && !check_player(data->map[(int)a.y][(int)a.x]))
		{
			h = sqrt(pow(First_inter.x - ply.x,2) + pow(First_inter.y - ply.y,2));
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
	t_point ply;

	ply.x = data->player.x - data->map_x;
	ply.y = data->player.y - data->map_y;
	
	
	First_inter.x = floor(ply.x / Z) * Z;
	if (facing_right(beta))
		First_inter.x += Z;
	First_inter.y = ply.y + ((First_inter.x - ply.x) * tan(beta));
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
			h = sqrt(pow(First_inter.x - ply.x,2) + pow(First_inter.y - ply.y,2));
			return(h);
		}
		if (data->map[(int)a.y][(int)a.x] != '0' && !check_player(data->map[(int)a.y][(int)a.x]))
		{
			h = sqrt(pow(First_inter.x - ply.x,2) + pow(First_inter.y - ply.y,2));
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
		r[i].x = data->player.x + (cos(sigma) * distance);
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
		DDA2(data, *seg,0xFFFFFFF);
		i++;
	}
}

void move_player(t_data *data)
{
	t_point p;
	t_point t;
	
	data->player.teta = normalize(data->player.teta);
	data->player.teta += data->player.turndirection * data->player.rotationspeed;
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