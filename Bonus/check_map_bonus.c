/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 00:46:37 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/07 20:24:40 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	check_valid_chars(char **s)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			if (!check_valid(s[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_line_comp(char **s, int t, int i)
{
	while (s[i])
	{
		t = ft_strlen(s[i]) - 1;
		if ((s[i][t] != ' ' && s[i][t] != '1')
			|| (s[i][0] != ' ' && s[i][0] != '1'))
			return (0);
		i++;
	}
	return (1);
}

int	check_line(char **s)
{
	int	i;
	int	j;
	int	len;
	int	t;

	t = 0;
	i = 0;
	j = 0;
	len = tab_len(s) -1;
	while (s[0][j])
	{
		if (s[0][j] != ' ' && s[0][j] != '1')
			return (0);
		j++;
	}
	j = 0;
	while (s[len][j])
	{
		if (s[len][j] != ' ' && s[len][j] != '1')
			return (0);
		j++;
	}
	if (!check_line_comp(s, t, i))
		return (0);
	return (1);
}

int	check_doors(char **s, int i, int j)
{
	if (s[i - 1][j] == '1' && s[i + 1][j] == '1')
		return (1);
	else if (s[i][j + 1] == '1' && s[i][j - 1] == '1')
		return (1);
	else
		return (0);
}

int	check_check(char **s, t_data *data)
{
	int	check;

	data->sp = 0;
	check = 1;
	check = check_valid_chars(s);
	check = check_line(s);
	return (check);
}
