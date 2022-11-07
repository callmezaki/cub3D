/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 00:11:26 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/07 02:12:28 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_symbol(t_data *data, double x, double y, int color)
{
	int		tmp;
	t_point	t;

	t.x = 4 + x;
	t.y = 4 + y;
	tmp = y;
	while (x < t.x)
	{
		y = tmp;
		while (y < t.y)
		{
			if (x > data->tile && x < data->tile * (MINI_CUB -1) && \
			y > data->tile && y < data->tile * (MINI_CUB -1))
				my_mlx_pixel_put(&data->window, x, y, color);
			y++;
		}
		x++;
	}
}

t_texture	get_t(char *path, t_texture tx, t_data *data)
{
	void	*img;

	img = mlx_xpm_file_to_image(data->window.mlx, path, &tx.width, &tx.height);
	if (!img)
		error_msg(data, 6);
	tx.tab = (int *)mlx_get_data_addr(img, &data->window.bits_per_pixel, \
	&data->window.line_length, &data->window.endian);
	return (tx);
}

void	get_texture(t_data *data)
{
	data->txtr.sp = get_t("../barrel.xpm", data->txtr.sp, data);
	data->txtr.north = get_t(data->no, data->txtr.north, data);
	data->txtr.south = get_t(data->so, data->txtr.south, data);
	data->txtr.east = get_t(data->ea, data->txtr.east, data);
	data->txtr.west = get_t(data->we, data->txtr.west, data);
	data->txtr.d_f0 = get_t("../F0.xpm", data->txtr.d_f0, data);
	data->txtr.d_f1 = get_t("../F1.xpm", data->txtr.d_f1, data);
	data->txtr.d_f2 = get_t("../F2.xpm", data->txtr.d_f2, data);
	data->txtr.d_f3 = get_t("../F3.xpm", data->txtr.d_f3, data);
	data->txtr.d_f4 = get_t("../F4.xpm", data->txtr.d_f4, data);
	data->txtr.d_f5 = get_t("../F5.xpm", data->txtr.d_f5, data);
	data->txtr.d_f6 = get_t("../F6.xpm", data->txtr.d_f6, data);
	data->txtr.s0 = get_t("./assets/sprite/R0.xpm", data->txtr.s0, data);
	data->txtr.s1 = get_t("./assets/sprite/R1.xpm", data->txtr.s1, data);
	data->txtr.s2 = get_t("./assets/sprite/R2.xpm", data->txtr.s2, data);
	data->txtr.s3 = get_t("./assets/sprite/R5.xpm", data->txtr.s3, data);
}

void	move_map(t_data *data)
{
	data->centre_p.x = data->player.x - (MINI_CUB * data->tile / 2);
	data->centre_p.y = data->player.y - (MINI_CUB * data->tile / 2);
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
