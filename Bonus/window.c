/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:21:13 by sgmira            #+#    #+#             */
/*   Updated: 2022/10/11 18:01:28 by zait-sli         ###   ########.fr       */
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
			// free(tab[i]);
			i++;
		}
		// free(tab);
	}
}

void	my_mlx_pixel_put(t_window *data, int x, int y, int color)
{
	char	*dst;

	if (x < W_width && x >=  0 && y < W_height && y >= 0)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
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
		exit_n_free(data, 1);
	}
	else if (key == KEY_SPACE)
	{
		if (data->oprn_door == 0)
			data->oprn_door = 1;
		else
			data->oprn_door = 0;
		draw(data);
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

int mouse_press(int key, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (key == 1)
		data->player.is_m_pressed = 1;
	return(0);
}

int mouse_release(int key, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (key == 1)
		data->player.is_m_pressed = 0;
	return(0);
}

int mouse_move(int x, int y, t_data *data)
{
	(void)y;
	
	if(!data->player.is_m_pressed)
		data->player.turndirection = 0;
	else if (data->player.is_m_pressed)
	{
		if (x <= W_width / 2)
			data->player.turndirection = -1;
		if (x > W_width / 2)
			data->player.turndirection = 1;
		if (x > W_width || x < 0)
			data->player.turndirection = 0;
		// printf("%d | %d\n", x, data->player.turndirection);
	}
	return(0);
}

void	init_window(t_data *data)
{
	data->player.turndirection = 0;
	data->player.walkdirection = 0;
	data->player.sides = 0;
	data->window.mlx = mlx_init();
	data->window.mlx_win = mlx_new_window(data->window.mlx, W_width, W_height, "Cub3d");
	get_texture(data);
	draw(data);
	mlx_loop_hook(data->window.mlx, run, data);
	mlx_hook(data->window.mlx_win, 2, 1L << 0, key_press, data);
	mlx_hook(data->window.mlx_win, 3, 0L, key_release, data);
	mlx_hook(data->window.mlx_win, 17, 0, you_quit, NULL);
	mlx_hook(data->window.mlx_win, 4, 0L, mouse_press, data);
	mlx_hook(data->window.mlx_win, 5, 0L, mouse_release, data);
	mlx_hook(data->window.mlx_win, 6, 0L, mouse_move, data);
	mlx_loop(data->window.mlx);
}