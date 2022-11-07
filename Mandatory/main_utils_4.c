/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 21:26:19 by sgmira            #+#    #+#             */
/*   Updated: 2022/11/07 01:35:37 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*check_assets_loop(t_data *data, char **s, char	*str, char	**t)
{
	while (s[data->i] && data->i < 7)
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
		{
			free(data->tmp);
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
	if (!check_duplicates(str))
	{
		free(str);
		return (0);
	}
	free(str);
	return (1);
}

void	check_map_err(char *s, t_data *data)
{
	int		p_count;

	data->i = 0;
	p_count = 0;
	while (s[data->i] && s[data->i + 1])
	{
		if ((s[data->i] == '\n' && s[data->i + 1] == '\n'))
		{
			break ;
		}
		if (check_player(s[data->i]))
			p_count++;
		data->i++;
	}
	if (p_count > 1 || p_count == 0)
		error_msg(data, 4);
}

int	check_empty_lines(char *s, t_data *data, int len)
{
	char	*a;
	char	*b;
	char	**t;

	while (s[++data->i])
	{
		if (s[data->i] != ' ' && s[data->i] != '\n'
			&& s[data->i] != '\t')
			exit_n_free(data, 1);
	}
	t = ft_split(s, '\n');
	data->i = 0;
	while (*t && t[++data->i])
	{
		a = ft_strtrim(t[data->i], " ");
		b = ft_strtrim(t[data->i - 1], " ");
		if (!a[0] && b[0])
			len++;
		if (a)
			free(a);
		if (b)
			free(b);
	}
	free_tab(t);
	return (len);
}

int	rgb_to_dec(t_color color)
{
	int	dec;

	dec = (color.r << 16) + (color.g << 8) + color.b;
	return (dec);
}
