/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:21:13 by sgmira            #+#    #+#             */
/*   Updated: 2022/09/22 23:17:46 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_window *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	move_right(t_data *data)
{	
	double x = (data->player.x + step) / Z;
	double y = (data->player.y / Z) ;
	if (data->map[(int)y][(int)x] != '1')
	{
		data->player.x += step;
	}
	draw_minimap(&data->window, data);
	draw_player(data);
	mlx_put_image_to_window(data->window.mlx, data->window.mlx_win, data->window.img, 0, 0);
}
void	move_left(t_data *data)
{	
	double x = (data->player.x - step) / Z;
	double y = (data->player.y / Z) ;
	if (data->map[(int)y][(int)x] != '1')
	{
		data->player.x -= step;
	}
	draw_minimap(&data->window, data);
	draw_player(data);
	mlx_put_image_to_window(data->window.mlx, data->window.mlx_win, data->window.img, 0, 0);
}
void	move_up(t_data *data)
{	
	double x = (data->player.x ) / Z;
	double y = (data->player.y - step)/ Z ;
	if (data->map[(int)y][(int)x] != '1')
	{
		data->player.y = data->player.y +(sin(data->player.teta) * (step));
		data->player.x = data->player.x +(cos(data->player.teta) * (step));
	}
	draw_minimap(&data->window, data);
	draw_player(data);
	mlx_put_image_to_window(data->window.mlx, data->window.mlx_win, data->window.img, 0, 0);
}
void	move_down(t_data *data)
{	
	double x = (data->player.x ) / Z;
	double y = (data->player.y + step) / Z ;
	if (data->map[(int)y][(int)x] != '1')
	{
		data->player.y = data->player.y +(sin(data->player.teta) * (step * -1));
		data->player.x = data->player.x +(cos(data->player.teta) * (step * -1));
	}
	draw_minimap(&data->window, data);
	draw_player(data);
	mlx_put_image_to_window(data->window.mlx, data->window.mlx_win, data->window.img, 0, 0);
}
void	rotate_left(t_data *data)
{	
	draw_minimap(&data->window, data);
	data->player.teta -= 0.2;
	data->player.teta = fmod(data->player.teta, 2 * M_PI);
	if (data->player.teta < 0)
		 data->player.teta += (M_PI * 2);
	draw_player(data);
	mlx_put_image_to_window(data->window.mlx, data->window.mlx_win, data->window.img, 0, 0);
}
void	rotate_right(t_data *data)
{	
	draw_minimap(&data->window, data);
	data->player.teta += 0.2;
	data->player.teta = fmod(data->player.teta, 2 * M_PI);
	if (data->player.teta < 0)
		 data->player.teta += (M_PI * 2);
	draw_player(data);
	mlx_put_image_to_window(data->window.mlx, data->window.mlx_win, data->window.img, 0, 0);
}

int	move_player(int key, t_data *data)
{

	if (key == KEY_D)
		move_right(data);
	else if (key == KEY_A)
		move_left(data);
	else if (key == KEY_W)
		move_up(data);
	else if (key == KEY_S)
		move_down(data);
	else if (key == LEFT)
		rotate_left(data);
	else if (key == RIGHT)
		rotate_right(data);
	return(0);
}

void	init_window(t_data *data)
{
	data->window.mlx = mlx_init();
	data->window.mlx_win = mlx_new_window(data->window.mlx, 1920, 1080, "Hello world!");
	data->window.img = mlx_new_image(data->window.mlx, 1920, 1080);
	data->window.addr = mlx_get_data_addr(data->window.img, &data->window.bits_per_pixel, &data->window.line_length,
								&data->window.endian);
	draw_minimap(&data->window ,data);
	draw_player(data);
	mlx_put_image_to_window(data->window.mlx, data->window.mlx_win, data->window.img, 0, 0);
	mlx_hook(data->window.mlx_win, 2, 1L << 0, move_player, data);
	mlx_loop(data->window.mlx);
}