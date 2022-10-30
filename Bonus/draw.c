/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:41:15 by zait-sli          #+#    #+#             */
/*   Updated: 2022/10/30 18:16:50 by zait-sli         ###   ########.fr       */
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
	while(y < W_HEIGHT)
	{
		x = 0;
		if(y == W_HEIGHT / 2)
			c = rgb_to_dec(data->F);
		while(x < W_WIDTH)
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

t_texture which_sprite_texture(t_data *data)
{
	if (data->an > 80)
		data->an  = 0;
	if (data->an >= 0 && data->an <= 20)
	{
		data->an++;
		return(data->txtr.s0);
	}
	else if (data->an > 20 && data->an <= 40)
	{
		data->an++;	
		return(data->txtr.s1);
	}
	else if(data->an > 40 && data->an <= 60)
	{
		data->an++;	
		return(data->txtr.s2);
	}
	else if(data->an > 60 && data->an <= 80)
	{
		data->an++;	
		return(data->txtr.s3);
	}
	else
	{
		data->an++;
		return(data->txtr.s3);
	}
}

void get_sprite_data(t_data *data)
{
	int i;
	int j = 0;
	int x = 0;
	t_point t;
	t_sprite *sps;

	sps = malloc(sizeof(t_sprite) * data->sp);
	while(data->map[j])
	{
		i = 0;
		while(data->map[j][i])
		{
			if (data->map[j][i] == '3')
			{
				sps[x].y = (j * Z) + data->map_y + (Z / 2);
				sps[x].x = (i * Z) + data->map_x + (Z / 2);
				sps[x].tx = data->txtr.sp;
				t.y =  sps[x].y - data->player.y;
				t.x =  sps[x].x - data->player.x;
				sps[x].angle = data->player.teta - atan2(t.y, t.x);
				if (sps[x].angle > M_PI)
					sps[x].angle -= 2 * M_PI; 
				if (sps[x].angle < -M_PI)
					sps[x].angle += 2 * M_PI;
				sps[x].angle = fabs(sps[x].angle);
				sps[x].vis = 0;
				if (sps[x].angle < D_RAYS + 0.2)
					sps[x].vis = 1;
				sps[x].distance = sqrt(pow(sps[x].x - data->player.x,2) + pow(sps[x].y - data->player.y,2));
				sps[x].drown = 0;
				x++;
			}
			i++;
		}
		j++;
	}
	data->sprites = sps;
	sort_sprites(data);
}


int check_dis(t_data *data, int x, int i)
{
	// if (data->r[i].hit_door)
	// {
	// 	if (data->sprites[x].distance <  data->r[i].dis_door)
	// 		return(1);
	// }
		if (data->sprites[x].distance < data->r[i].distance)
			return(1);
	// }
	return(0);
}

void draw_sprite(t_data *data,int x)
{
	int i = 0;
	int j = 0;
	// int x = 0;
	t_point t;
	double rad = (FOV) * (M_PI / 180);

	// x = 0;
	data->sprites[x].drown = 1;
	// while(x < data->sp)
	// {dro
		if (data->sprites[x].vis == 1)
		{
			t_texture tx = which_sprite_texture(data);
			t_point txtr_off;
			double distance_to_proj = (W_WIDTH / 2)  / tan(rad / 2);
			double sprite_height = (Z / data->sprites[x].distance) * distance_to_proj;
			double sprite_width = sprite_height;
			double sprite_topY = (W_HEIGHT / 2) - (sprite_height /  2);
			if (sprite_topY < 0)
				sprite_topY = 0;
			double sprite_bottomY = (W_HEIGHT / 2) + (sprite_height /  2);
			if (sprite_bottomY > W_HEIGHT)
				sprite_bottomY = W_HEIGHT;
			t.y =  data->sprites[x].y - data->player.y;
			t.x =  data->sprites[x].x - data->player.x;
			data->sprites[x].angle = normalize(atan2(t.y, t.x) - data->player.teta);
			double sprite_sc_posX = tan(data->sprites[x].angle) * distance_to_proj;
			double sprite_leftX = (W_WIDTH / 2) + sprite_sc_posX  - (sprite_width / 2);
			double sprite_rightX = sprite_leftX + sprite_width;
			i = (int)sprite_leftX;
			while(i < sprite_rightX)
			{
				if (i >= 0 && i < W_WIDTH  && check_dis(data, x, i))
				{
					double t = (tx.width / sprite_width);
					txtr_off.x = (i - sprite_leftX) * t;
					j = sprite_topY;
					while(j < sprite_bottomY)
					{
						double distance_from_top = j + ((int)sprite_height / 2 ) - (W_HEIGHT / 2);
						txtr_off.y = distance_from_top * (tx.height / sprite_height);
						int h = (tx.width * (int)txtr_off.y) + (int)txtr_off.x;
						if (h >=0 && h < (tx.height * tx.width) && tx.tab[h] != 3642478)
						{
							my_mlx_pixel_put(&data->window, i, j, tx.tab[h]);
						}
						j++;
					}
				}
				i++;
			}
		}
	// 	x++;
	// }	
}

void draw_rest_sprites(t_data *data)
{
	int x = 0;

	while(x < data->sp)
	{
		if (data->sprites[x].drown == 0)
			draw_sprite(data,x);
		x++;
	}
}

int draw(t_data *data)
{
	t_segment seg;

	mlx_clear_window(data->window.mlx, data->window.mlx_win);
	data->window.img = mlx_new_image(data->window.mlx, W_WIDTH, W_HEIGHT);
	data->window.addr = mlx_get_data_addr(data->window.img, &data->window.bits_per_pixel, &data->window.line_length,
								&data->window.endian);
	move_map(data);
	draw_background(data);
	move_player(data);
	claculate_rays(data);
	draw_walls(data);
	get_sprite_data(data);
	draw_doors(data);
	draw_rest_sprites(data);
	// draw_sprites(data);
	draw_minimap_frame(data);
	player_symbol(data, data->player.x - 2, data->player.y - 2, 0);
	draw_rays(&seg, data);
	draw_minimap(data);
	free(data->r);
	free(data->sprites);
	mlx_put_image_to_window(data->window.mlx, data->window.mlx_win, data->window.img, 0, 0);
	mlx_destroy_image(data->window.mlx, data->window.img);
	return(0);
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
			else if ((data->map[i][j] == '0') || (data->map[i][j] == '3') || check_player(data->map[i][j]));
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
		t.x = data->sprites[i].x - 2;
		t.y = data->sprites[i].y - 2;
		// if (data->sprites[i].vis == 1)
		// 	player_symbol(data,t.x,t.y, 0xEEC643);
		// else
			player_symbol(data,t.x,t.y, 0xEEC643);
		i++;
	}
	return(0);
}

int draw_minimap_frame(t_data *data)
{
	int i = 0;
	int j = 0;
	t_point p;
	
	while(i < MINI_CUB)
	{
		p.x = 0;
		p.y = i * Z ;
		j = 0;
		while(j < MINI_CUB)
		{
			if ((i == 0 || (i == MINI_CUB - 1)) || (j == 0 || (j == MINI_CUB - 1)))
				ft_block(data, p.x,p.y,0);	
			else
				ft_block(data, p.x,p.y,0x6E7E85);	
			p.x += Z;
			j++;
		}
		i++;
	}
	return(0);
}