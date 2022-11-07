/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:41:15 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/07 19:48:11 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_background(t_data *data)
{
	int	x;
	int	y;
	int	c;

	x = 0;
	y = 0;
	c = rgb_to_dec(data->c);
	while (y < W_HEIGHT)
	{
		x = 0;
		if (y == W_HEIGHT / 2)
			c = rgb_to_dec(data->f);
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
	t_segment	seg;

	mlx_clear_window(data->window.mlx, data->window.mlx_win);
	data->window.img = mlx_new_image(data->window.mlx, W_WIDTH, W_HEIGHT);
	data->window.addr = mlx_get_data_addr(data->window.img, \
	&data->window.bits_per_pixel, &data->window.line_length, \
	&data->window.endian);
	move_map(data);
	draw_background(data);
	move_player(data);
	claculate_rays(data);
	draw_walls(data);
	get_sprite_data(data);
	draw_doors(data);
	draw_rest_sprites(data);
	draw_minimap_frame(data);
	player_symbol(data, data->player.x - 2, data->player.y - 2, 0);
	draw_rays(&seg, data);
	draw_minimap(data);
	free(data->r);
	free(data->sprites);
	mlx_put_image_to_window(data->window.mlx, data->window.mlx_win, \
	data->window.img, 0, 0);
	mlx_destroy_image(data->window.mlx, data->window.img);
	return (0);
}

void	mini_sp(t_data *data)
{
	int		i;
	t_point	t;

	i = 0;
	while (i < data->sp)
	{
		t.x = data->sprites[i].x - 2;
		t.y = data->sprites[i].y - 2;
		player_symbol(data, t.x, t.y, 0xEEC643);
		i++;
	}
}

int	draw_minimap(t_data *data)
{
	int		i;
	int		j;
	t_point	p;

	i = 0;
	while (data->map[i])
	{
		p.x = data->map_x;
		p.y = data->map_y + (i * data->tile);
		j = 0;
		while (data->map[i][j])
		{
			if ((data->map[i][j] == '0') || (data->map[i][j] == '3') \
			|| check_player(data->map[i][j]) || data->map[i][j] == ' ')
				;
			else
				ft_block2(data, p.x, p.y, get_color(data->map[i][j]));
			p.x += data->tile;
			j++;
		}
		i++;
	}
	mini_sp(data);
	return (0);
}

int	draw_minimap_frame(t_data *data)
{
	int		i;
	int		j;
	t_point	p;

	i = 0;
	while (i < MINI_CUB)
	{
		p.x = 0;
		p.y = i * data->tile ;
		j = 0;
		while (j < MINI_CUB)
		{
			if ((i == 0 || (i == MINI_CUB - 1)) || (j == 0 || \
			(j == MINI_CUB - 1)))
				;
			else
				ft_block(data, p.x, p.y, 0x6E7E85);
			p.x += data->tile;
			j++;
		}
		i++;
	}
	return (0);
}
