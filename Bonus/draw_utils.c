/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 00:11:26 by zait-sli          #+#    #+#             */
/*   Updated: 2022/10/09 14:49:53 by sgmira           ###   ########.fr       */
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
		
	img = mlx_xpm_file_to_image(data->window.mlx, data->NO, &data->txtr.north.width, &data->txtr.north.height);
	data->txtr.north.tab = (int *)mlx_get_data_addr(img, &data->window.bits_per_pixel, &data->window.line_length, &data->window.endian);
	img = mlx_xpm_file_to_image(data->window.mlx, data->SO, &data->txtr.south.width, &data->txtr.south.height);
	data->txtr.south.tab = (int *)mlx_get_data_addr(img, &data->window.bits_per_pixel, &data->window.line_length, &data->window.endian);
	img = mlx_xpm_file_to_image(data->window.mlx, data->EA, &data->txtr.east.width, &data->txtr.east.height);
	data->txtr.east.tab = (int *)mlx_get_data_addr(img, &data->window.bits_per_pixel, &data->window.line_length, &data->window.endian);
	img = mlx_xpm_file_to_image(data->window.mlx, data->WE, &data->txtr.west.width, &data->txtr.west.height);
	data->txtr.west.tab = (int *)mlx_get_data_addr(img, &data->window.bits_per_pixel, &data->window.line_length, &data->window.endian);
	img = mlx_xpm_file_to_image(data->window.mlx, "assets/door.xpm", &data->txtr.door.width, &data->txtr.door.height);
	data->txtr.door.tab = (int *)mlx_get_data_addr(img, &data->window.bits_per_pixel, &data->window.line_length, &data->window.endian);
}

void move_map(t_data *data)
{
	data->centre_p.x = data->player.x - (mini_cub * Z / 2);
	data->centre_p.y = data->player.y - (mini_cub * Z / 2);
	data->player.x -= data->centre_p.x;
	data->player.y -= data->centre_p.y;
	data->map_x -= data->centre_p.x;
	data->map_y -= data->centre_p.y;
}

int rgb_to_dec(t_color color)
{
	int dec;

	dec = (color.R << 16) + (color.G << 8) + color.B;
	return(dec);
}