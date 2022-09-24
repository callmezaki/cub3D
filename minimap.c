/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:22:07 by zait-sli          #+#    #+#             */
/*   Updated: 2022/09/24 02:32:41 by zait-sli         ###   ########.fr       */
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

int draw_minimap(t_data *data)
{
	t_block block;
	int i = 0;
	int j = 0;
	

	block.x0 = 0;
	block.y0 = -Z;
	block.x1 = 0;
	block.y1 = 0;
	mlx_clear_window(data->window.mlx, data->window.mlx_win);
	data->window.img = mlx_new_image(data->window.mlx, W_width, W_height);
	data->window.addr = mlx_get_data_addr(data->window.img, &data->window.bits_per_pixel, &data->window.line_length,
								&data->window.endian);
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
	draw_player(data);
	draw_walls(data);
	mlx_put_image_to_window(data->window.mlx, data->window.mlx_win, data->window.img, 0, 0);
	mlx_destroy_image(data->window.mlx, data->window.img);
	return(0);
}

void	draw_walls(t_data *data)
{
	int i = 0;
	t_segment seg;

	while(i < rays)
	{
		double per_distance = data->r[i].distance * cos(data->r[i].alpha - data->player.teta);
		double distance_to_proj = rays / tan(60 / 2);
		double proj_wall_height = (120 / per_distance) * distance_to_proj;
		double wall_top_pixel = (W_height / 2) - (proj_wall_height / 2);
		int h = (int)proj_wall_height;
		seg.x0 = i*2;
		seg.y0 = wall_top_pixel;
		seg.x1 = i*2;
		seg.y1 = wall_top_pixel + h;
		DDA(data, seg,0xffffff);
		i++;
	}
	
}

void	draw_rays(t_segment *seg, t_data *data)
{
	double h = 0;
	int i = 0;
	int j = rays / 2;
	t_ray* r;
	r = malloc(sizeof(t_ray) * rays);

	seg->x0 = data->player.x;
	seg->y0 = data->player.y;
	while(1)
	{
		double x = (data->player.x  + (cos(data->player.teta) * h)) / Z;
		double y = (data->player.y + (sin(data->player.teta) * h)) / Z;
		if (data->map[(int)y][(int)x] != '0' && !check_player(data->map[(int)y][(int)x]))
		{
			seg->x1 = data->player.x + (cos(data->player.teta) * h);
			seg->y1 = data->player.y + (sin(data->player.teta) * h);
			break;
		}
		h+=step;
	}
	DDA(data, *seg,0xf02b79);
	while(i < rays / 2)
	{
		h = 0;
		while(1)
		{
			double x = (data->player.x  + (cos(data->player.teta + (-1 * i * D_rays)) * h)) / Z;
			double y = (data->player.y + (sin(data->player.teta + (-1 * i * D_rays)) * h)) / Z;
			if (data->map[(int)y][(int)x] != '0' && !check_player(data->map[(int)y][(int)x]))
			{
				seg->x1 = data->player.x + (cos(data->player.teta + (-1 * i * D_rays)) * h);
				seg->y1 = data->player.y + (sin(data->player.teta + (-1 * i * D_rays)) * h);
				break;
			}
			h+=step;
		}
		r[j].x = seg->x1;
		r[j].y = seg->y1;
		r[j].distance = h;
		r[j].alpha = data->player.teta + (-1 * i * D_rays);
		DDA(data, *seg,0xf02b79);
		i++;
		j--;
	}
	i = 0;
	j = rays / 2;
	while(i < rays / 2)
	{
		h = 0;
		while(1)
		{
			double x = (data->player.x  + (cos(data->player.teta + (i * D_rays)) * h)) / Z;
			double y = (data->player.y + (sin(data->player.teta + (i * D_rays)) * h)) / Z;
			if (data->map[(int)y][(int)x] != '0' && !check_player(data->map[(int)y][(int)x]))
			{
				seg->x1 = data->player.x + (cos(data->player.teta + (i * D_rays)) * h);
				seg->y1 = data->player.y + (sin(data->player.teta + (i * D_rays)) * h);
				break;
			}
			h+=step;
		}
		r[j].x = seg->x1;
		r[j].y = seg->y1;
		r[j].distance = h;
		r[j].alpha = data->player.teta + (i * D_rays);
		DDA(data, *seg,0xf02b79);
		i++;
		j++;
	}
	data->r = r;
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