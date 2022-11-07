/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 04:48:42 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/07 19:48:31 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	key_press_cond(int key, t_data *data)
{
	if (key == KEY_A)
	{
		data->player.sides = 1;
		data->player.walkdirection = -1;
	}
	else if (key == KEY_D)
	{
		data->player.sides = 1;
		data->player.walkdirection = 1;
	}
	else if (key == LEFT)
		data->player.turndirection = -1;
	else if (key == RIGHT)
		data->player.turndirection = 1;
	else if (key == KEY_ESC)
		exit_n_free(data, 0);
}

int	key_press(int key, t_data *data)
{
	t_point	p;

	p.y = data->player.y - data->map_y;
	p.x = data->player.x - data->map_x;
	if (key == KEY_W)
	{
		data->player.sides = 0;
		data->player.walkdirection = 1;
	}
	else if (key == KEY_S)
	{
		data->player.sides = 0;
		data->player.walkdirection = -1;
	}
	key_press_cond(key, data);
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == KEY_W)
		data->player.walkdirection = 0;
	else if (key == KEY_S)
		data->player.walkdirection = 0;
	if (key == KEY_A)
		data->player.walkdirection = 0;
	else if (key == KEY_D)
		data->player.walkdirection = 0;
	else if (key == LEFT)
		data->player.turndirection = 0;
	else if (key == RIGHT)
		data->player.turndirection = 0;
	return (0);
}

int	mouse_press(int key, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (key == 1)
		data->player.is_m_pressed = 1;
	return (0);
}

int	mouse_release(int key, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (key == 1)
		data->player.is_m_pressed = 0;
	return (0);
}
