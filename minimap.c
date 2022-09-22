/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:22:07 by zait-sli          #+#    #+#             */
/*   Updated: 2022/09/22 23:29:14 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int get_color(char c)
{
	int color = 0;
	
	if (c == '0' || check_player(c))
	{
		color = 16777215;
	}
	else if (c == '1')
		color = 8421504;
	return (color);
}

void draw_minimap(t_window *win ,t_data *data)
{
	t_block block;
	int i = 0;
	int j = 0;

	block.x0 = 0;
	block.y0 = -Z;
	block.x1 = 0;
	block.y1 = 0;
	while(data->map[i])
	{
		block.x0 = 0;
		block.x1 = block.x0 + Z;
		block.y0 += Z;
		block.y1 = block.y0 + Z;
		j = 0;
		while(data->map[i][j])
		{
			if (data->map[i][j] == ' ');
			else
			{
				block.color = get_color(data->map[i][j]);
				ft_block(win, block);
			}
			block.x0 = block.x1;
			block.x1 += Z;
			j++;
		}
		i++;
	}
}
void draw_player(t_data *data)
{
	t_segment seg;
	
	seg.x0 = data->player.x;
	seg.y0 = data->player.y;
	seg.x1 = data->player.x  + (cos(data->player.teta) * 60);
	seg.y1 = data->player.y + (sin(data->player.teta) * 60);
	// printf("%f  %f  %f  %f\n", seg.x0, seg.y0, seg.x1, seg.y1);
	
	DDA(data, seg);
}