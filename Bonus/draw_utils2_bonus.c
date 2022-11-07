/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 04:23:40 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/07 19:48:16 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	get_color(char c)
{
	int	color;

	color = 0;
	if (c == '0' || check_player(c))
	{
		color = 16777215;
	}
	else if (c == '1')
		color = 0xB7CECE;
	else if (c == '2')
		color = 0x011627;
	else
		color = 0x808080;
	return (color);
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

double	normalize(double teta)
{
	teta = fmod(teta, 2 * M_PI);
	if (teta < 0)
		teta += (M_PI * 2);
	return (teta);
}

void	draw_rays(t_segment *seg, t_data *data)
{
	seg->x0 = data->player.x;
	seg->y0 = data->player.y;
	seg->x1 = data->r[RAYS / 2].x;
	seg->y1 = data->r[RAYS / 2].y;
	dda2(data, *seg, 0);
}
