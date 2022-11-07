/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:21:13 by sgmira            #+#    #+#             */
/*   Updated: 2022/11/07 01:43:52 by sgmira           ###   ########.fr       */
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

	if (x < W_WIDTH && x >= 0 && y < W_HEIGHT && y >= 0)
	{
		dst = data->addr
			+ (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *) dst = color;
	}
}

int	you_quit(void)
{
	write(1, "-------You Quit!-------\n", 25);
	exit(EXIT_SUCCESS);
}

int	mouse_move(int x, int y, t_data *data)
{
	(void)y;
	if (!data->player.is_m_pressed)
		data->player.turndirection = 0;
	else if (data->player.is_m_pressed)
	{
		if (x <= W_WIDTH / 2)
			data->player.turndirection = -1;
		if (x > W_WIDTH / 2)
			data->player.turndirection = 1;
		if (x > W_WIDTH || x < 0)
			data->player.turndirection = 0;
	}
	return (0);
}

void	init_window(t_data *data)
{
	data->player.turndirection = 0;
	data->player.walkdirection = 0;
	data->player.sides = 0;
	data->window.mlx = mlx_init();
	data->window.mlx_win = mlx_new_window(data->window.mlx,
			W_WIDTH, W_HEIGHT, "Cub3d");
	get_texture(data);
	draw(data);
	mlx_loop_hook(data->window.mlx, run, data);
	mlx_loop(data->window.mlx);
}
