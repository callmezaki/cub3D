/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:22:07 by zait-sli          #+#    #+#             */
/*   Updated: 2022/09/23 19:25:43 by sgmira           ###   ########.fr       */
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
	data->window.img = mlx_new_image(data->window.mlx, 1920, 1080);
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
	mlx_put_image_to_window(data->window.mlx, data->window.mlx_win, data->window.img, 0, 0);
	mlx_destroy_image(data->window.mlx, data->window.img);
	return(0);
}

void	draw_rays(t_segment *seg, t_data *data)
{
	int i = 0;
	
	seg->x0 = data->player.x;
	seg->y0 = data->player.y;
	seg->x1 = data->player.x  + (cos(data->player.teta) * 300);
	seg->y1 = data->player.y + (sin(data->player.teta) * 300);
	DDA(data, *seg);
	while(i < 100)
	{
		seg->x1 = data->player.x  + (cos(data->player.teta + (i * 0.002)) * 300);
		seg->y1 = data->player.y + (sin(data->player.teta + (i * 0.002)) * 300);
		DDA(data, *seg);
		i++;
	}
	i = 0;
	while(i < 100)
	{
		seg->x1 = data->player.x  + (cos(data->player.teta + (-1 * i * 0.002)) * 300);
		seg->y1 = data->player.y + (sin(data->player.teta + (-1 * i * 0.002)) * 300);
		DDA(data, *seg);
		i++;
	}
}

void draw_player(t_data *data)
{
	t_segment seg;
	
	data->player.teta += data->player.turndirection * data->player.rotationspeed;
	data->player.x += (cos(data->player.teta) * data->player.walkdirection * data->player.movespeed);
	data->player.y += (sin(data->player.teta) * data->player.walkdirection * data->player.movespeed);
	draw_rays(&seg, data);
}