/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 00:47:00 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/07 00:48:28 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_map_width(t_data *data, int y)
{
	if (y <= data->map_height)
	{
		return (ft_strlen(data->map[y]));
	}
	return (-1);
}

int	check_valid(int c)
{
	if (c == '1' || c == '0' || c == '2' || c == 'N'
		|| c == 'W' || c == 'E' || c == 'S' || c == ' ' || c == '3'
		|| c == '\n' || c == '\t')
		return (1);
	return (0);
}

int	check_player(char c)
{
	if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
		return (1);
	return (0);
}

void	check_zero(char **s, int i, int j, t_data *data)
{
	char	c;

	c = s[i - 1][j];
	if (c == '1' || c == '0' || c == '2' || c == '3' || check_player(c))
	{
		c = s[i + 1][j];
		if (c == '1' || c == '0' || c == '2' || c == '3' || check_player(c))
		{
			c = s[i][j + 1];
			if (c == '1' || c == '0' || c == '2' || c == '3' || check_player(c))
			{
				c = s[i][j - 1];
				if (c == '1' || c == '0' || c == '2' || c == '3' || \
				check_player(c))
					return ;
			}
		}
	}
	error_msg(data, 4);
}
