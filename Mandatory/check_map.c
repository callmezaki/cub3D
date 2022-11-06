/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 00:46:37 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/06 20:19:22 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_checkif_1(char *s, t_data *data)
{
	if (s[data->i] != ' ' && s[data->i] != '\n'
		&& s[data->i] != '\t' && s[data->i] != '1')
	{
		printf("%c\n", s[data->i]);
		printf("Errrrroooor\n");
		exit_n_free(data, 1);
	}
}

void	map_checkif_2(int p_count, t_data *data)
{
	if (p_count > 1 || p_count == 0)
	{
		printf("P Error\n");
		exit_n_free(data, 1);
	}
}

void	map_checkif_3(int len, t_data *data)
{
	if (len > 1)
	{
		printf("Errrrroooor7\n");
		exit_n_free(data, 1);
	}
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
	{
		printf("P Error\n");
		exit_n_free(data, 1);
	}
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
	{
		printf("Errrrroooor7\n");
		exit_n_free(data, 1);
	}
	s = ft_strtrim2_f(s, " \n\t");
	return (s);
}
