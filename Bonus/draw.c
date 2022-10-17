/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:41:15 by zait-sli          #+#    #+#             */
/*   Updated: 2022/10/17 22:21:10 by zait-sli         ###   ########.fr       */
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


void sort_sprites(t_data *data)
{
	int i = 0;
	int j = 0;
	t_sprite t;

	while(i < data->sp)
	{
		j = 0;
		while(j + 1 < data->sp)
		{
			if (data->sprites[j].distance < data->sprites[j + 1].distance)
			{
				t = data->sprites[j + 1];
				data->sprites[j + 1] = data->sprites[j];
				data->sprites[j] = t;
			}
			j++;
		}
		i++;
	}
}

void draw_sprites(t_data *data)
{
	int i;
	int j = 0;
	int x = 0;
	t_point t;
	double rad = (FOV) * (M_PI / 180);

	data->sprites = malloc(sizeof(t_sprite) * data->sp);
	while(data->map[j])
	{
		i = 0;
		while(data->map[j][i])
		{
			if (data->map[j][i] == '3')
			{
				data->sprites[x].y = (j * Z) + data->map_y;
				data->sprites[x].x = (i * Z) + data->map_x;
				data->sprites[x].tx = data->txtr.sp;
				t.y =  data->sprites[x].y - data->player.y;
				t.x =  data->sprites[x].x - data->player.x;
				data->sprites[x].angle = data->player.teta - atan2(t.y, t.x);
				if (data->sprites[x].angle > M_PI)
					data->sprites[x].angle -= 2 * M_PI; 
				if (data->sprites[x].angle < -M_PI)
					data->sprites[x].angle += 2 * M_PI;
				data->sprites[x].angle = fabs(data->sprites[x].angle);
				data->sprites[x].vis = 0;
				if (data->sprites[x].angle < D_rays + 0.2)
					data->sprites[x].vis = 1;
				data->sprites[x].distance = sqrt(pow(data->sprites[x].x - data->player.x,2) + pow(data->sprites[x].y - data->player.y,2));
				x++;
			}
			i++;
		}
		j++;
	}
	sort_sprites(data);
	x = 0;
	while(x < data->sp)
	{
		if (data->sprites[x].vis == 1)
		{
			t_point txtr_off;
			double distance_to_proj = (W_width / 2)  / tan(rad / 2);
			double sprite_height = (Z / data->sprites[x].distance) * distance_to_proj;
			double sprite_width = sprite_height;
			double sprite_topY = (W_height / 2) - (sprite_height /  2);
			if (sprite_topY < 0)
				sprite_topY = 0;
			double sprite_bottomY = (W_height / 2) + (sprite_height /  2);
			if (sprite_bottomY > W_height)
				sprite_bottomY = W_height;
			data->sprites[x].angle = normalize(atan2(t.y, t.x) - data->player.teta);
			double sprite_sc_posX = tan(data->sprites[x].angle) * distance_to_proj;
			double sprite_leftX = (W_width / 2) + sprite_sc_posX;
			double sprite_rightX = sprite_leftX + sprite_width;
			i = sprite_leftX;
			t_texture tx = data->sprites[x].tx;
			while(i < sprite_rightX)
			{
				double t = (tx.width / sprite_width);
				txtr_off.x = (i - sprite_leftX) * t;
				j = sprite_topY;
				while(j < sprite_bottomY)
				{
					double distance_from_top = j + (sprite_height / 2 ) - (W_height / 2);
					txtr_off.y = distance_from_top * (tx.height / sprite_height);
					if (tx.tab[(tx.width * (int)txtr_off.y) + (int)txtr_off.x] != 16711935 && data->sprites[x].distance < data->r[i].distance)
						my_mlx_pixel_put(&data->window, i, j, tx.tab[(tx.width * (int)txtr_off.y) + (int)txtr_off.x]);
					j++;
				}
				i++;
			}
		}
		x++;
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
	draw_sprites(data);
	draw_minimap_frame(data);
	draw_rays(&seg, data);
	free(data->r);
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
	draw_sprites(data);
	draw_minimap_frame(data);
	draw_rays(&seg, data);
	free(data->r);
	draw_minimap(data);
	player_symbol(data, data->player.x - 2, data->player.y - 2, 0);
	mlx_put_image_to_window(data->window.mlx, data->window.mlx_win, data->window.img, 0, 0);
	mlx_destroy_image(data->window.mlx, data->window.img);
}

int draw_minimap(t_data *data)
{
	int i = 0;
	int j = 0;
	t_point p;
	t_point t;
	
	while(data->map[i])
	{
		p.x = data->map_x;
		p.y = data->map_y + (i * Z) ;
		j = 0;
		while(data->map[i][j])
		{
			if (data->map[i][j] == ' ');
			else if ((data->map[i][j] == '0') || check_player(data->map[i][j]));
			else if (data->map[i][j] == '3')
			{
				t.x = (j * Z) - 2 + data->map_x + (Z / 2);
				t.y = (i * Z) - 2 + data->map_y + (Z / 2);
				if (data->sprites[0].vis == 1)
					player_symbol(data,t.x,t.y, 0xEEC643);
				else
					player_symbol(data,t.x,t.y, 0);
			}
			else
				ft_block2(data, p.x,p.y,get_color(data->map[i][j]));
			p.x += Z;
			j++;
		}
		i++;
	}
	i = 0;
	while(i < data->sp)
	{
		t.x = data->sprites[i].x + (Z / 2) - 2;
		t.y = data->sprites[i].y + (Z / 2) - 2;
		if (data->sprites[0].vis == 1)
			player_symbol(data,t.x,t.y, 0xEEC643);
		else
			player_symbol(data,t.x,t.y, 0);
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