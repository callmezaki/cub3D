/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 03:00:28 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/07 02:07:38 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_map_comp(int check, t_data *data)
{
	if (!check)
		error_msg(data, 4);
}

void	check_map(char **s, t_data *data)
{
	int	i;
	int	j;
	int	check;

	s = ft_trima3(s);
	check = check_check(s, data);
	i = 1;
	while (s[i + 1] && check)
	{
		j = 1;
		while (s[i][j] && check)
		{
			if (s[i][j] == '0' || s[i][j] == '2' || s[i][j] == '3' || \
			check_player(s[i][j]))
				check_zero(s, i, j, data);
			if (s[i][j] == '2')
				check = check_doors(s, i, j);
			if (s[i][j] == '3')
				data->sp++;
			j++;
		}
		i++;
	}
	check_map_comp(check, data);
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
