/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_4_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 21:12:13 by sgmira            #+#    #+#             */
/*   Updated: 2022/11/07 23:03:53 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	parse_walls(t_data *data, char **args)
{
	data->i = txtr_error(args, "NO");
	if (data->i < 0)
		exit_n_free(data, 1);
	check_space(args[data->i], data);
	if (ft_strchr(args[data->i], '.'))
		data->no = ft_strdup(ft_strchr(args[data->i], '.'));
	else
		error_msg(data, 1);
	check_path(data->no, data);
	data->i = txtr_error(args, "SO");
	if (data->i < 0)
		exit_n_free(data, 1);
	check_space(args[data->i], data);
	if (ft_strchr(args[data->i], '.'))
		data->so = ft_strdup(ft_strchr(args[data->i], '.'));
	else
		error_msg(data, 1);
	check_path(data->so, data);
	parse_walls_2(data, args);
}

char	*check_assets_loop(t_data *data, char **s, char	*str, char	**t)
{
	while (s[data->i] && data->i < 6)
	{
		t = ft_split(s[data->i], ' ');
		if (t[0][0] && (!ft_strcmp(t[0], "NO") || !ft_strcmp(t[0], "SO")
			|| !ft_strcmp(t[0], "WE") || !ft_strcmp(t[0], "EA")
			|| !ft_strcmp(t[0], "C") || !ft_strcmp(t[0], "F")))
		{
			data->tmp[0] = s[data->i][0];
			str = ft_strjoin_2(str, data->tmp);
			data->j++;
		}
		else
			error_msg(data, 1);
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
