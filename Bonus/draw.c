/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:41:15 by zait-sli          #+#    #+#             */
/*   Updated: 2022/10/05 18:25:05 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	t_segment seg;

	mlx_clear_window(data->window.mlx, data->window.mlx_win);
	data->window.img = mlx_new_image(data->window.mlx, W_width, W_height);
	data->window.addr = mlx_get_data_addr(data->window.img, &data->window.bits_per_pixel, &data->window.line_length,
								&data->window.endian);
	move_map(data);
	draw_background(data);
	move_player(data);
	claculate_rays(data);
	draw_walls(data);
	draw_minimap_frame(data);
	draw_rays(&seg, data);
	draw_minimap(data);
	player_symbol(data, data->player.x - 2, data->player.y - 2, 0);
	mlx_put_image_to_window(data->window.mlx, data->window.mlx_win, data->window.img, 0, 0);
	mlx_destroy_image(data->window.mlx, data->window.img);
	return(0);
}

void	rotate_player(t_data *data)
{
	t_segment seg;

	mlx_clear_window(data->window.mlx, data->window.mlx_win);
	data->window.img = mlx_new_image(data->window.mlx, W_width, W_height);
	data->window.addr = mlx_get_data_addr(data->window.img, &data->window.bits_per_pixel, &data->window.line_length,
								&data->window.endian);
	draw_background(data);
	claculate_rays(data);
	draw_walls(data);
	draw_minimap_frame(data);
	draw_rays(&seg, data);
	draw_minimap(data);
	mlx_put_image_to_window(data->window.mlx, data->window.mlx_win, data->window.img, 0, 0);
	mlx_destroy_image(data->window.mlx, data->window.img);
}

int draw_minimap(t_data *data)
{
	int i = 0;
	int j = 0;
	t_point p;
	
	while(data->map[i])
	{
		p.x = data->map_x;
		p.y = data->map_y + i * Z ;
		j = 0;
		while(data->map[i][j])
		{
			if (data->map[i][j] == ' ');
			else if ((data->map[i][j] == '0') || check_player(data->map[i][j]));
			else
				ft_block2(data, p.x,p.y,get_color(data->map[i][j]));
			p.x += Z;
			j++;
		}
		i++;
	}
	return(0);
}

int draw_minimap_frame(t_data *data)
{
	int i = 0;
	int j = 0;
	t_point p;
	
	while(i < mini_cub)
	{
		p.x = 0;
		p.y = i * Z ;
		j = 0;
		while(j < mini_cub)
		{
			if ((i == 0 || (i == mini_cub - 1)) || (j == 0 || (j == mini_cub - 1)))
				ft_block(data, p.x,p.y,0);	
			else
				ft_block(data, p.x,p.y,10676939);	
			p.x += Z;
			j++;
		}
		i++;
	}
	return(0);
}