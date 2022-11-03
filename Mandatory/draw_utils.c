/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 00:11:26 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/03 01:06:57 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_texture(t_data *data)
{
	void	*img;

	img = mlx_xpm_file_to_image(data->window.mlx, data->NO,
			&data->txtr.north.width, &data->txtr.north.height);
	data->txtr.north.tab = (int *)mlx_get_data_addr(img,
			&data->window.bits_per_pixel,
			&data->window.line_length, &data->window.endian);
	img = mlx_xpm_file_to_image(data->window.mlx, data->SO,
			&data->txtr.south.width, &data->txtr.south.height);
	data->txtr.south.tab = (int *)mlx_get_data_addr(img,
			&data->window.bits_per_pixel,
			&data->window.line_length, &data->window.endian);
	img = mlx_xpm_file_to_image(data->window.mlx, data->EA,
			&data->txtr.east.width, &data->txtr.east.height);
	data->txtr.east.tab = (int *)mlx_get_data_addr(img,
			&data->window.bits_per_pixel,
			&data->window.line_length, &data->window.endian);
	img = mlx_xpm_file_to_image(data->window.mlx, data->WE,
			&data->txtr.west.width, &data->txtr.west.height);
	data->txtr.west.tab = (int *)mlx_get_data_addr(img,
			&data->window.bits_per_pixel,
			&data->window.line_length, &data->window.endian);
}

void	move_map(t_data *data)
{
	data->centre_p.x = data->player.x - (MINI_CUB * Z / 2);
	data->centre_p.y = data->player.y - (MINI_CUB * Z / 2);
	data->player.x -= data->centre_p.x;
	data->player.y -= data->centre_p.y;
	data->map_x -= data->centre_p.x;
	data->map_y -= data->centre_p.y;
}

int	rgb_to_dec(t_color color)
{
	int	dec;

	dec = (color.r << 16) + (color.g << 8) + color.b;
	return (dec);
}

int	facing_down(double beta)
{
	if (beta > 0 && beta < M_PI)
		return (1);
	return (0);
}

int	facing_right(double beta)
{
	if (beta < M_PI / 2 || beta > 1.5 * M_PI)
		return (1);
	return (0);
}
