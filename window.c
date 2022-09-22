/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:21:13 by sgmira            #+#    #+#             */
/*   Updated: 2022/09/22 15:40:26 by sgmira           ###   ########.fr       */
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
	if (data->map[data->player.x][data->player.y + 1] != '1')
	{
		data->map[data->player.x][data->player.y] = '0';
		data->map[data->player.x][data->player.y + 1] = 'N';
	}
	
	draw_minimap(&data->window, data);
}

int	move_player(int key, t_data *data)
{
	// t_data *data;
	// data = (t_data *) param;

	printf("%s\n", data->map[4]);
	if (key == KEY_D)
		move_right(data);
	// else if (key == KEY_A)
	// 	move_left(data);
	// else if (key == KEY_W)
	// 	move_up(data);
	// else if (key == KEY_S)
	// 	move_down(data);
	return(0);
}

void	init_window(t_data *data)
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	data->window.img = mlx_new_image(mlx, 1920, 1080);
	data->window.addr = mlx_get_data_addr(data->window.img, &data->window.bits_per_pixel, &data->window.line_length,
								&data->window.endian);
	draw_minimap(&data->window ,data);
	mlx_put_image_to_window(mlx, mlx_win, data->window.img, 0, 0);
	mlx_hook(mlx_win, 2, 1L << 0, move_player, data);
	mlx_loop(mlx);
}