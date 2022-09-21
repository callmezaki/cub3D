/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:22:07 by zait-sli          #+#    #+#             */
/*   Updated: 2022/09/21 18:02:36 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int get_color(char c)
{
	int color = 0;
	
	if (c == '0')
	{
		color = 16777215;
	}
	if (check_player(c))
	{
		color = 879875;
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
	block.y0 = -20;
	block.x1 = 0;
	block.y1 = 0;
	while(data->map[i])
	{
		block.x0 = 0;
		block.x1 = block.x0 + 20;
		block.y0 += 20;
		block.y1 = block.y0 + 20;
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
			block.x1 += 20;
			j++;
		}
		i++;
	}
}