/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:21:13 by sgmira            #+#    #+#             */
/*   Updated: 2022/09/21 16:53:46 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_window *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	init_window()
{
	void	*mlx;
	void	*mlx_win;
	t_window	window;
	t_block     block;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	window.img = mlx_new_image(mlx, 1920, 1080);
	window.addr = mlx_get_data_addr(window.img, &window.bits_per_pixel, &window.line_length,
								&window.endian);
	ft_block(&window, &block);
	mlx_put_image_to_window(mlx, mlx_win, window.img, 0, 0);
	mlx_loop(mlx);
}