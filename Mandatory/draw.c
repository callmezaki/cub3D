/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:41:15 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/03 01:06:43 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_background(t_data *data)
{
	int	x;
	int	y;
	int	c;

	x = 0;
	y = 0;
	c = rgb_to_dec(data->C);
	while (y < W_HEIGHT)
	{
		x = 0;
		if (y == W_HEIGHT / 2)
			c = rgb_to_dec(data->F);
		while (x < W_WIDTH)
		{
			my_mlx_pixel_put(&data->window, x, y, c);
			x++;
		}
		y++;
	}
}

int	draw(t_data *data)
{
	mlx_clear_window(data->window.mlx, data->window.mlx_win);
	data->window.img = mlx_new_image(data->window.mlx, W_WIDTH, W_HEIGHT);
	data->window.addr = mlx_get_data_addr(data->window.img,
			&data->window.bits_per_pixel,
			&data->window.line_length, &data->window.endian);
	draw_background(data);
	move_player(data);
	claculate_rays(data);
	draw_walls(data);
	free(data->r);
	mlx_put_image_to_window(data->window.mlx,
		data->window.mlx_win, data->window.img, 0, 0);
	mlx_destroy_image(data->window.mlx, data->window.img);
	return (0);
}

void	rotate_player(t_data *data)
{
	mlx_clear_window(data->window.mlx, data->window.mlx_win);
	data->window.img = mlx_new_image(data->window.mlx, W_WIDTH, W_HEIGHT);
	data->window.addr = mlx_get_data_addr(data->window.img,
			&data->window.bits_per_pixel,
			&data->window.line_length, &data->window.endian);
	draw_background(data);
	claculate_rays(data);
	draw_walls(data);
	free(data->r);
	mlx_put_image_to_window(data->window.mlx,
		data->window.mlx_win, data->window.img, 0, 0);
	mlx_destroy_image(data->window.mlx, data->window.img);
}

int	draw_minimap(t_data *data)
{
	int		i;
	int		j;
	t_point	p;

	i = 0;
	j = 0;
	while (data->map[i])
	{
		p.x = data->map_x;
		p.y = data->map_y + i * Z ;
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == ' ')
				;
			else if ((data->map[i][j] == '0') || check_player(data->map[i][j]));
			else
				ft_block2(data, p.x, p.y, get_color(data->map[i][j]));
			p.x += Z;
			j++;
		}
		i++;
	}
	return (0);
}

int	draw_minimap_frame(t_data *data)
{
	int		i;
	int		j;
	t_point	p;

	i = 0;
	j = 0;
	while (i < MINI_CUB)
	{
		p.x = 0;
		p.y = i * Z ;
		j = 0;
		while (j < MINI_CUB)
		{
			if ((i == 0 || (i == MINI_CUB - 1))
				|| (j == 0 || (j == MINI_CUB - 1)))
				ft_block(data, p.x, p.y, 0);
			else
				ft_block(data, p.x, p.y, 10676939);
			p.x += Z;
			j++;
		}
		i++;
	}
	return (0);
}
