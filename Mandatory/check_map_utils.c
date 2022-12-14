/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 00:47:00 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/07 18:54:31 by zait-sli         ###   ########.fr       */
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
	if (c == '1' || c == '0' || c == 'N'
		|| c == 'W' || c == 'E' || c == 'S' || c == ' ')
		return (1);
	return (0);
}

int	check_player(char c)
{
	if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
		return (1);
	return (0);
}

void	else_free(char	*tmp, char	**t)
{
	free(tmp);
	free_tab(t);
}

void	check_zero(char **s, int i, int j)
{
	if (s[i - 1][j] == '1' || s[i - 1][j] == '0' || check_player(s[i - 1][j]))
	{
		if (s[i + 1][j] == '1' || s[i + 1][j] == '0'
			|| check_player(s[i + 1][j]))
		{
			if (s[i][j + 1] == '1' || s[i][j + 1] == '0'
				|| check_player(s[i][j + 1]))
			{
				if (s[i][j - 1] == '1' || s[i][j - 1] == '0'
					|| check_player(s[i][j - 1]))
					return ;
			}
		}
	}
	printf("Error zero\n");
	exit(1);
}
