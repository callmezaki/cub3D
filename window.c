/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:21:13 by sgmira            #+#    #+#             */
/*   Updated: 2022/09/26 18:40:34 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

void	my_mlx_pixel_put(t_window *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	you_quit(void)
{
	write(1, "-------You Quit!-------\n", 25);
	exit(EXIT_SUCCESS);
}

int key_press(int key, t_data *data)
{
	if (key == KEY_W)
	{
		data->player.sides = 0;
		data->player.walkdirection = 1;
	}
	else if (key == KEY_S)
	{
		data->player.sides = 0;
		data->player.walkdirection = -1;
	}
	if (key == KEY_A)
	{
		data->player.sides = 1;
		data->player.walkdirection = -1;
	}
	else if (key == KEY_D)
	{
		data->player.sides = 1;
		data->player.walkdirection = 1;
	}
	else if (key == LEFT)
		data->player.turndirection = -1;
	else if (key == RIGHT)
		data->player.turndirection = 1;
	else if (key == KEY_ESC)
	{
		free_tab(data->map);
		exit(EXIT_SUCCESS);
	}
	return(0);
}

int key_release(int key, t_data *data)
{
	if (key == KEY_W)
		data->player.walkdirection = 0;
	else if (key == KEY_S)
		data->player.walkdirection = 0;
	if (key == KEY_A)
		data->player.walkdirection = 0;
	else if (key == KEY_D)
		data->player.walkdirection = 0;
	else if (key == LEFT)
		data->player.turndirection = 0;
	else if (key == RIGHT)
		data->player.turndirection = 0;
	return(0);
}

void	init_window(t_data *data)
{
	data->player.turndirection = 0;
	data->player.walkdirection = 0;
	data->player.sides = 0;
	data->player.rotationspeed = (2 * M_PI / 180);
	data->window.mlx = mlx_init();
	data->window.mlx_win = mlx_new_window(data->window.mlx, W_width, W_height, "Cub3d");
	// data->window.img = mlx_new_image(data->window.mlx, 1920, 1080);
	// data->window.addr = mlx_get_data_addr(data->window.img, &data->window.bits_per_pixel, &data->window.line_length,
	// 							&data->window.endian);
	// // draw_minimap(data);
	// // draw_player(data);
	// mlx_put_image_to_window(data->window.mlx, data->window.mlx_win, data->window.img, 0, 0);
	draw(data);
	mlx_loop_hook(data->window.mlx, run, data);
	mlx_hook(data->window.mlx_win, 2, 1L << 0, key_press, data);
	mlx_hook(data->window.mlx_win, 3, 0L, key_release, data);
	mlx_hook(data->window.mlx_win, 17, 0, you_quit, NULL);
	mlx_loop(data->window.mlx);
}