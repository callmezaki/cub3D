/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_3_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 21:02:50 by sgmira            #+#    #+#             */
/*   Updated: 2022/11/07 22:23:49 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	txtr_error(char **args, char *key)
{
	int	i;

	i = search_indx(args, key);
	if (i < 0)
		write(2, "Texture_ERROR!\n", 16);
	return (i);
}

void	exit_n_free(t_data *data, int t)
{
	(void)data;
	if (data->no)
		free(data->no);
	if (data->ea)
		free(data->ea);
	if (data->we)
		free(data->we);
	if (data->so)
		free(data->so);
	if (data->map)
		free_tab(data->map);
	if (data)
		free(data);
	exit(t);
}

void	get_player_data(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 1;
		while (data->map[i][j])
		{
			if (check_player(data->map[i][j]))
			{
				get_player_data_calc(data, i, j);
				break ;
			}
			j++;
		}
		i++;
	}
}

char	*get_data_loop(t_data *data, char	*str, int fd, char	*temp)
{
	while (str)
	{
		str = get_next_line(fd);
		if (str)
		{
			if (data->i < 7)
			{
				if (ft_trima(&str, data->i))
				{
					str = ft_strjoin_2(str, "\n");
					data->i++;
				}
			}
			temp = ft_strjoin_2(temp, str);
			free(str);
		}
	}
	return (temp);
}

void	get_data(int fd, t_data *data)
{
	char	*str;
	char	*temp;

	data->i = 0;
	str = malloc(1);
	if (!str)
		exit_n_free(data, 1);
	str[0] = '\0';
	temp = malloc(1);
	if (!temp)
		exit_n_free(data, 1);
	temp[0] = '\0';
	temp = get_data_loop(data, str, fd, temp);
	parse_data(data, temp);
}
