/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:21:13 by sgmira            #+#    #+#             */
/*   Updated: 2022/09/23 19:36:43 by sgmira           ###   ########.fr       */
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

// void	move_right(t_data *data)
// {	
// 	double x = (data->player.x + step) / Z;
// 	double y = (data->player.y / Z) ;
// 	if (data->map[(int)y][(int)x] != '1')
// 	{
// 		data->player.x += step;
// 	}
// 	draw_minimap(&data->window, data);
// 	draw_player(data);
// 	mlx_put_image_to_window(data->window.mlx, data->window.mlx_win, data->window.img, 0, 0);
// }
// void	move_left(t_data *data)
// {	
// 	double x = (data->player.x - step) / Z;
// 	double y = (data->player.y / Z) ;
// 	if (data->map[(int)y][(int)x] != '1')
// 	{
// 		data->player.x -= step;
// 	}
// 	draw_minimap(&data->window, data);
// 	draw_player(data);
// 	mlx_put_image_to_window(data->window.mlx, data->window.mlx_win, data->window.img, 0, 0);
// }
// void	move_up(t_data *data)
// {	
// 	double x = (data->player.x ) / Z;
// 	double y = (data->player.y - step)/ Z ;
// 	if (data->map[(int)y][(int)x] != '1')
// 	{
// 		data->player.y = data->player.y +(sin(data->player.teta) * (step));
// 		data->player.x = data->player.x +(cos(data->player.teta) * (step));
// 	}
// 	draw_minimap(&data->window, data);
// 	draw_player(data);
// 	mlx_put_image_to_window(data->window.mlx, data->window.mlx_win, data->window.img, 0, 0);
// }
// void	move_down(t_data *data)
// {	
// 	double x = (data->player.x) / Z;
// 	double y = (data->player.y + step) / Z ;
// 	if (data->map[(int)y][(int)x] != '1')
// 	{
// 		data->player.y = data->player.y +(sin(data->player.teta) * (step * -1));
// 		data->player.x = data->player.x +(cos(data->player.teta) * (step * -1));
// 	}
// 	draw_minimap(&data->window, data);
// 	draw_player(data);
// 	mlx_put_image_to_window(data->window.mlx, data->window.mlx_win, data->window.img, 0, 0);
// }
// void	rotate_left(t_data *data)
// {	
// 	draw_minimap(&data->window, data);
// 	data->player.teta -= 0.1;
// 	data->player.teta = fmod(data->player.teta, 2 * M_PI);
// 	if (data->player.teta < 0)
// 		 data->player.teta += (M_PI * 2);
// 	draw_player(data);
// 	mlx_put_image_to_window(data->window.mlx, data->window.mlx_win, data->window.img, 0, 0);
// }
// void	rotate_right(t_data *data)
// {	
// 	draw_minimap(&data->window, data);
// 	data->player.teta += 0.1;
// 	data->player.teta = fmod(data->player.teta, 2 * M_PI);
// 	if (data->player.teta < 0)
// 		 data->player.teta += (M_PI * 2);
// 	draw_player(data);
// 	mlx_put_image_to_window(data->window.mlx, data->window.mlx_win, data->window.img, 0, 0);
// }

// int	move_player(int key, t_data *data)
// {
		
// 	if (key == KEY_D)
// 		move_right(data);
// 	else if (key == KEY_A)
// 		move_left(data);
// 	else if (key == KEY_W)
// 		move_up(data);
// 	else if (key == KEY_S)
// 		move_down(data);
// 	else if (key == LEFT)
// 		rotate_left(data);
// 	else if (key == RIGHT)
// 		rotate_right(data);
// 	else if (key == KEY_ESC)
// 	{
// 		free_tab(data->map);
// 		exit(EXIT_SUCCESS);
// 	}
// 	return(0);
// }

int	you_quit(void)
{
	write(1, "-------You Quit!-------\n", 25);
	exit(EXIT_SUCCESS);
}

int key_press(int key, t_data *data)
{
	if (key == KEY_W)
		data->player.walkdirection = 1;
	else if (key == KEY_S)
		data->player.walkdirection = -1;
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
	data->player.rotationangle = M_PI / 2;
	data->player.rotationspeed = (3 * M_PI / 180);
	data->player.movespeed = 4;
	data->window.mlx = mlx_init();
	data->window.mlx_win = mlx_new_window(data->window.mlx, 1920, 1080, "Cub3d");
	// data->window.img = mlx_new_image(data->window.mlx, 1920, 1080);
	// data->window.addr = mlx_get_data_addr(data->window.img, &data->window.bits_per_pixel, &data->window.line_length,
	// 							&data->window.endian);
	// // draw_minimap(data);
	// // draw_player(data);
	// mlx_put_image_to_window(data->window.mlx, data->window.mlx_win, data->window.img, 0, 0);
	mlx_loop_hook(data->window.mlx, draw_minimap, data);
	mlx_hook(data->window.mlx_win, 2, 1L << 0, key_press, data);
	mlx_hook(data->window.mlx_win, 3, 0L, key_release, data);
	mlx_hook(data->window.mlx_win, 17, 0, you_quit, NULL);
	mlx_loop(data->window.mlx);
}