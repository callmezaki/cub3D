/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 00:46:37 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/07 18:53:49 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_checkif_1(char *s, t_data *data)
{
	if (s[data->i] != ' ' && s[data->i] != '\n'
		&& s[data->i] != '\t' && s[data->i] != '1')
	{
		printf("%c\n", s[data->i]);
		error_msg(data, 4);
	}
}

void	map_checkif_2(int p_count, t_data *data)
{
	if (p_count > 1 || p_count == 0)
		error_msg(data, 4);
}

void	map_checkif_3(int len, t_data *data)
{
	if (len > 1)
		error_msg(data, 4);
}

void	check_path_2(char *d, t_data *data)
{
	if (access(d, F_OK | R_OK))
		error_msg(data, 8);
}

char	*intial_map_check(char *s, char **t, t_data *data)
{
	int		len;
	char	*h;
	int		p_count;

	data->i = 0;
	len = 0;
	p_count = 0;
	while (data->i < 6)
	{
		len += ft_strlen(t[data->i]);
		data->i++;
	}
	h = ft_strdup(&s[len + data->i]);
	free(s);
	s = h;
	check_map_err(s, data);
	len = 0;
	len = check_empty_lines(s, data, len);
	if (len > 1)
		error_msg(data, 4);
	s = ft_strtrim2_f(s, " \n\t");
	return (s);
}
