/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 00:13:42 by sgmira            #+#    #+#             */
/*   Updated: 2022/11/03 00:21:00 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_color(char c)
{
	int	color;

	color = 0;
	if (c == '0' || check_player(c))
	{
		color = 16777215;
	}
	else if (c == '1')
		color = 35184;
	return (color);
}

t_texture	which_texture(t_data *data, int i)
{
	if (data->r[i].h_or_v == 1)
	{
		if (normalize(data->r[i].alpha) >= M_PI
			&& normalize(data->r[i].alpha) < 2 * M_PI)
			return (data->txtr.north);
		else
			return (data->txtr.south);
	}
	else
	{
		if (normalize(data->r[i].alpha) >= (M_PI / 2)
			&& normalize(data->r[i].alpha) < 3 * (M_PI / 2))
			return (data->txtr.east);
		else
			return (data->txtr.west);
	}	
}

double	findmod(double a, double b)
{
	double	mod;

	if (a < 0)
		mod = -a;
	else
		mod = a;
	if (b < 0)
		b = -b;
	while (mod >= b)
		mod = mod - b;
	if (a < 0)
		return (-mod);
	return (mod);
}

double	normalize(double teta)
{
	teta = findmod(teta, 2 * M_PI);
	if (teta < 0)
		teta += (M_PI * 2);
	return (teta);
}

void	draw_rays(t_segment *seg, t_data *data)
{
	int	i;

	i = 0;
	seg->x0 = data->player.x;
	seg->y0 = data->player.y;
	while (i < RAYS)
	{
		seg->x1 = data->r[i].x;
		seg->y1 = data->r[i].y;
		dda2(data, *seg, 0xFFFFFFF);
		i++;
	}
}
