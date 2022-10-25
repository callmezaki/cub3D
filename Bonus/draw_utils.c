/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 00:11:26 by zait-sli          #+#    #+#             */
/*   Updated: 2022/10/25 01:53:09 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    player_symbol(t_data *data, double x, double y,int color)
{
	int tmp;
	t_point t;

	t.x = 4 + x;
	t.y = 4 + y;
	
	tmp = y;
    while(x < t.x)
    {
        y = tmp;
        while(y < t.y)
        {
           	my_mlx_pixel_put(&data->window, x, y, color);
            y++;
        }
        x++;
    }
}

void	get_texture(t_data *data)
{
	void *img;
		
	img = mlx_xpm_file_to_image(data->window.mlx, "../barrel.xpm", &data->txtr.sp.width, &data->txtr.sp.height);
	data->txtr.sp.tab = (int *)mlx_get_data_addr(img, &data->window.bits_per_pixel, &data->window.line_length, &data->window.endian);
	img = mlx_xpm_file_to_image(data->window.mlx, data->NO, &data->txtr.north.width, &data->txtr.north.height);
	data->txtr.north.tab = (int *)mlx_get_data_addr(img, &data->window.bits_per_pixel, &data->window.line_length, &data->window.endian);
	img = mlx_xpm_file_to_image(data->window.mlx, data->SO, &data->txtr.south.width, &data->txtr.south.height);
	data->txtr.south.tab = (int *)mlx_get_data_addr(img, &data->window.bits_per_pixel, &data->window.line_length, &data->window.endian);
	img = mlx_xpm_file_to_image(data->window.mlx, data->EA, &data->txtr.east.width, &data->txtr.east.height);
	data->txtr.east.tab = (int *)mlx_get_data_addr(img, &data->window.bits_per_pixel, &data->window.line_length, &data->window.endian);
	img = mlx_xpm_file_to_image(data->window.mlx, data->WE, &data->txtr.west.width, &data->txtr.west.height);
	data->txtr.west.tab = (int *)mlx_get_data_addr(img, &data->window.bits_per_pixel, &data->window.line_length, &data->window.endian);

	img = mlx_xpm_file_to_image(data->window.mlx, data->DO, &data->txtr.door.width, &data->txtr.door.height);
	data->txtr.door.tab = (int *)mlx_get_data_addr(img, &data->window.bits_per_pixel, &data->window.line_length, &data->window.endian);
	
	img = mlx_xpm_file_to_image(data->window.mlx, "../F0.xpm", &data->txtr.d_f0.width, &data->txtr.d_f0.height);
	data->txtr.d_f0.tab = (int *)mlx_get_data_addr(img, &data->window.bits_per_pixel, &data->window.line_length, &data->window.endian);
	
	img = mlx_xpm_file_to_image(data->window.mlx, "../F1.xpm", &data->txtr.d_f1.width, &data->txtr.d_f1.height);
	data->txtr.d_f1.tab = (int *)mlx_get_data_addr(img, &data->window.bits_per_pixel, &data->window.line_length, &data->window.endian);

	img = mlx_xpm_file_to_image(data->window.mlx, "../F2.xpm", &data->txtr.d_f2.width, &data->txtr.d_f2.height);
	data->txtr.d_f2.tab = (int *)mlx_get_data_addr(img, &data->window.bits_per_pixel, &data->window.line_length, &data->window.endian);

	img = mlx_xpm_file_to_image(data->window.mlx, "../F3.xpm", &data->txtr.d_f3.width, &data->txtr.d_f3.height);
	data->txtr.d_f3.tab = (int *)mlx_get_data_addr(img, &data->window.bits_per_pixel, &data->window.line_length, &data->window.endian);

	img = mlx_xpm_file_to_image(data->window.mlx, "../F4.xpm", &data->txtr.d_f4.width, &data->txtr.d_f4.height);
	data->txtr.d_f4.tab = (int *)mlx_get_data_addr(img, &data->window.bits_per_pixel, &data->window.line_length, &data->window.endian);

	img = mlx_xpm_file_to_image(data->window.mlx, "../F5.xpm", &data->txtr.d_f5.width, &data->txtr.d_f5.height);
	data->txtr.d_f5.tab = (int *)mlx_get_data_addr(img, &data->window.bits_per_pixel, &data->window.line_length, &data->window.endian);

	img = mlx_xpm_file_to_image(data->window.mlx, "../F6.xpm", &data->txtr.d_f6.width, &data->txtr.d_f6.height);
	data->txtr.d_f6.tab = (int *)mlx_get_data_addr(img, &data->window.bits_per_pixel, &data->window.line_length, &data->window.endian);
	
	// img = mlx_xpm_file_to_image(data->window.mlx, "/assets/sprite/R0.xpm", &data->txtr.s0.width, &data->txtr.s0.height);
	// data->txtr.s0.tab = (int *)mlx_get_data_addr(img, &data->window.bits_per_pixel, &data->window.line_length, &data->window.endian);
	
	// img = mlx_xpm_file_to_image(data->window.mlx, "/assets/sprite/R1.xpm", &data->txtr.s1.width, &data->txtr.s1.height);
	// data->txtr.s1.tab = (int *)mlx_get_data_addr(img, &data->window.bits_per_pixel, &data->window.line_length, &data->window.endian);
	
	// img = mlx_xpm_file_to_image(data->window.mlx, "/assets/sprite/R3.xpm", &data->txtr.s2.width, &data->txtr.s2.height);
	// data->txtr.s2.tab = (int *)mlx_get_data_addr(img, &data->window.bits_per_pixel, &data->window.line_length, &data->window.endian);
	
	// img = mlx_xpm_file_to_image(data->window.mlx, "/assets/sprite/R5.xpm", &data->txtr.s3.width, &data->txtr.s3.height);
	// data->txtr.s3.tab = (int *)mlx_get_data_addr(img, &data->window.bits_per_pixel, &data->window.line_length, &data->window.endian);
	
}

void move_map(t_data *data)
{
	data->centre_p.x = data->player.x - (MINI_CUB * Z / 2);
	data->centre_p.y = data->player.y - (MINI_CUB * Z / 2);
	data->player.x -= data->centre_p.x;
	data->player.y -= data->centre_p.y;
	data->map_x -= data->centre_p.x;
	data->map_y -= data->centre_p.y;
}

int rgb_to_dec(t_color color)
{
	int dec;

	dec = (color.r << 16) + (color.g << 8) + color.b;
	return(dec);
}