/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 00:11:26 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/07 01:28:55 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture	get_t(char *path, t_texture tx, t_data *data)
{
	void	*img;

	img = mlx_xpm_file_to_image(data->window.mlx, path, &tx.width, &tx.height);
	if (!img)
		error_msg(data, 3);
	tx.tab = (int *)mlx_get_data_addr(img, &data->window.bits_per_pixel, \
	&data->window.line_length, &data->window.endian);
	return (tx);
}

void	get_texture(t_data *data)
{
	data->txtr.north = get_t(data->no, data->txtr.north, data);
	data->txtr.south = get_t(data->so, data->txtr.south, data);
	data->txtr.east = get_t(data->ea, data->txtr.east, data);
	data->txtr.west = get_t(data->we, data->txtr.west, data);
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

int	facing_down(double beta)
{
	if (beta > 0 && beta < M_PI)
		return (1);
	return (0);
}

int	facing_right(double beta)
{
	if (beta < M_PI / 2 || beta > 1.5 * M_PI)
		return (1);
	return (0);
}
