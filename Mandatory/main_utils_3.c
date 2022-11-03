/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 00:55:08 by sgmira            #+#    #+#             */
/*   Updated: 2022/11/03 00:59:00 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_duplicates(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		j = i + 1;
		while (str[j])
		{
			if (str[j] == str[i])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_free(char	*str)
{
	if (!check_duplicates(str))
	{
		free(str);
		return (0);
	}
	return (1);
}

void	exit_n_free(t_data *data, int t)
{
	(void)data;
	free(data->NO);
	free(data->EA);
	free(data->WE);
	free(data->SO);
	free_tab(data->map);
	free(data);
	// system("leaks cub3d");
	exit(t);
}

void	get_player_data(t_data *data)
{
	data->i = -1;
	data->j = -1;
	while (data->map[++data->i])
	{
		data->j = 0;
		while (data->map[data->i][++data->j])
		{
			if (check_player(data->map[data->i][data->j]))
			{
				data->player.facing = data->map[data->i][data->j];
				data->player.x = (data->j * Z) + (Z / 2);
				data->player.y = (data->i * Z) + (Z / 2);
				if (data->player.facing == 'N')
					data->player.teta = 3 * M_PI / 2;
				else if (data->player.facing == 'S')
					data->player.teta = M_PI / 2;
				else if (data->player.facing == 'E')
					data->player.teta = 2 * M_PI;
				else if (data->player.facing == 'W')
					data->player.teta = M_PI;
				break ;
			}
		}
	}
}

void	parse_data(t_data *data, char *temp)
{
	char	**s;
	char	*str;
	char	*tmp;
	char	**t;

	str = ft_strdup("");
	tmp = ft_strdup("");
	t = NULL;
	s = ft_split(temp, '\n');
	if (check_assets(s, str, tmp, t, data))
	{
		free_tab(s);
		puts("FAIL");
		exit_n_free(data, 1);
	}
	parse_walls(data, s);
	get_colors(data, s);
	temp = intial_map_check(temp, s, data);
	data->map = ft_split(temp, '\n');
	free_tab(s);
	free(temp);
	check_map(data->map, data);
	get_player_data(data);
	data->map_height = tab_len(data->map);
}