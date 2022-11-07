/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 20:53:58 by sgmira            #+#    #+#             */
/*   Updated: 2022/11/07 23:04:03 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	search_indx(char **args, char *indx)
{
	int	i;

	i = 0;
	if (ft_strlen(indx) == 2)
	{
		while (args[i])
		{
			if (args[i][0] == indx[0] && args[i][1] == indx[1])
				return (i);
			i++;
		}
	}
	else if (ft_strlen(indx) == 1)
	{
		while (args[i])
		{
			if (args[i][0] == indx[0])
				return (i);
			i++;
		}
	}
	return (-1);
}

int	tab_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	check_space(char *s, t_data *data)
{
	char	**t;

	t = ft_split(s, ' ');
	if (tab_len(t) != 2)
	{
		free_tab(t);
		error_msg(data, 1);
	}
	free_tab(t);
}

void	check_path(char *d, t_data *data)
{
	if (access(d, F_OK | R_OK))
		error_msg(data, 5);
}

void	parse_walls_2(t_data *data, char **args)
{
	data->i = txtr_error(args, "WE");
	if (data->i < 0)
		exit_n_free(data, 1);
	check_space(args[data->i], data);
	if (ft_strchr(args[data->i], '.'))
		data->we = ft_strdup(ft_strchr(args[data->i], '.'));
	else
		error_msg(data, 1);
	check_path(data->we, data);
	data->i = txtr_error(args, "EA");
	if (data->i < 0)
		exit_n_free(data, 1);
	check_space(args[data->i], data);
	if (ft_strchr(args[data->i], '.'))
		data->ea = ft_strdup(ft_strchr(args[data->i], '.'));
	else
		error_msg(data, 1);
	check_path(data->ea, data);
}
