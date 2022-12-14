/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 00:41:39 by sgmira            #+#    #+#             */
/*   Updated: 2022/11/07 23:07:35 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	check_map(char **s, t_data *data)
{
	int	i;
	int	j;
	int	check;

	s = ft_trima3(s);
	check = check_valid_chars(s);
	check = check_line(s);
	i = 1;
	while (s[i + 1] && check)
	{
		j = 1;
		while (s[i][j])
		{
			if (s[i][j] == '0' || check_player(s[i][j]))
				check_zero(s, i, j);
			j++;
		}
		i++;
	}
	if (!check)
		error_msg(data, 4);
}

void	init_vars(t_data *data)
{
	if (W_HEIGHT > 2000 || W_HEIGHT < 300 || W_WIDTH < 300 || W_WIDTH > 2000)
	{
		printf("Error in Window Dimentions\n");
		exit(1);
	}
	data->tile = W_HEIGHT / 90;
	data->rotation_speed = (3 * M_PI / 180);
	data->rays_degr = (FOV / 2) * (M_PI / 180);
	data->rays_inc = data->rays_degr / (W_WIDTH / 2);
}
