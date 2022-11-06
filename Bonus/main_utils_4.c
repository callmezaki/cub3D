/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 21:12:13 by sgmira            #+#    #+#             */
/*   Updated: 2022/11/06 22:48:50 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_walls(t_data *data, char **args)
{
	data->i = txtr_error(args, "NO");
	if (data->i < 0)
		exit_n_free(data, 1);
	check_space(args[data->i], data);
	data->no = ft_strdup(ft_strchr(args[data->i], '.'));
	check_path(data->no, data);
	data->i = txtr_error(args, "DO");
	if (data->i < 0)
		exit_n_free(data, 1);
	check_space(args[data->i], data);
	data->doo = ft_strdup(ft_strchr(args[data->i], '.'));
	check_path(data->no, data);
	parse_walls_2(data, args);
}

char	*check_assets_loop(t_data *data, char **s, char	*str, char	**t)
{
	while (s[data->i] && data->i < 7)
	{
		t = ft_split(s[data->i], ' ');
		if (t[0][0] && (!ft_strcmp(t[0], "NO") || !ft_strcmp(t[0], "SO")
			|| !ft_strcmp(t[0], "WE") || !ft_strcmp(t[0], "EA")
			|| !ft_strcmp(t[0], "C") || !ft_strcmp(t[0], "F")
			|| !ft_strcmp(t[0], "DO")))
		{
			data->tmp[0] = s[data->i][0];
			str = ft_strjoin_2(str, data->tmp);
			data->j++;
		}
		else
		{
			if (t[0][0])
				free_tab(t);
			break ;
		}
		if (t[0][0])
			free_tab(t);
		data->i++;
	}
	return (str);
}

int	check_assets(char **s, t_data *data)
{
	char	*str;
	char	**t;

	t = NULL;
	str = ft_strdup("");
	data->tmp = ft_strdup("");
	data->i = 0;
	data->j = 0;
	str = check_assets_loop(data, s, str, t);
	free(data->tmp);
	if (!check_duplicates(str))
	{
		free(str);
		return (0);
	}
	free(str);
	return (1);
}

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
