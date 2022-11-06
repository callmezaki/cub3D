/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 04:46:09 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/06 04:47:24 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_dis(t_data *data, int x, int i)
{
	if (data->sprites[x].distance < data->r[i].distance)
		return (1);
	return (0);
}

void	sort_sprites(t_data *data)
{
	int			i;
	int			j;
	t_sprite	t;

	i = 0;
	while (i < data->sp)
	{
		j = 0;
		while (j + 1 < data->sp)
		{
			if (data->sprites[j].distance < data->sprites[j + 1].distance)
			{
				t = data->sprites[j + 1];
				data->sprites[j + 1] = data->sprites[j];
				data->sprites[j] = t;
			}
			j++;
		}
		i++;
	}
}

t_texture	which_sprite_texture(t_data *data)
{
	if (data->an > 80)
		data->an = 0;
	if (data->an >= 0 && data->an <= 20)
	{
		data->an++;
		return (data->txtr.s0);
	}
	else if (data->an > 20 && data->an <= 40)
	{
		data->an++;
		return (data->txtr.s1);
	}
	else if (data->an > 40 && data->an <= 60)
	{
		data->an++;
		return (data->txtr.s2);
	}
	else if (data->an > 60 && data->an <= 80)
	{
		data->an++;
		return (data->txtr.s3);
	}
	else
		return (data->txtr.s3);
}
