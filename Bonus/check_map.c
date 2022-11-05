/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 00:46:37 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/04 22:14:29 by sgmira           ###   ########.fr       */
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

void	check_map_comp(int	check, t_data *data)
{
	if (!check)
	{
		printf("Error check_map\n");
		exit_n_free(data, 1);
	}
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
				check_zero(s, i, j);
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

char	*intial_map_check(char *s, char **t, t_data *data)
{
	int		len;
	char	*a;
	char	*b;
	char	*h;
	int		p_count;

	data->i = 0;
	len = 0;
	p_count = 0;
	while (data->i < 7)
	{
		len += ft_strlen(t[data->i]);
		data->i++;
	}
	h = ft_strdup(&s[len + data->i]);
	free(s);
	s = h;
	data->i = 0;
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
	{
		printf("P Error\n");
		exit_n_free(data, 1);
	}
	while (s[data->i])
	{
		if (s[data->i] != ' ' && s[data->i] != '\n'
			&& s[data->i] != '\t' && s[data->i] != '1')
		{
			printf("Errrrroooor\n");
			exit_n_free(data, 1);
		}
		data->i++;
	}
	t = ft_split(s, '\n');
	len = 0;
	data->i = 1;
	while (t[data->i])
	{
		a = ft_strtrim(t[data->i], " ");
		b = ft_strtrim(t[data->i - 1], " ");
		if (!a[0] && b[0])
			len++;
		if (a)
			free(a);
		if (b)
			free(b);
		data->i++;
	}
	if (t[0][0])
		free_tab(t);
	if (len > 1)
	{
		printf("Errrrroooor7\n");
		exit_n_free(data, 1);
	}
	s = ft_strtrim2_f(s, " \n\t");
	return (s);
}
