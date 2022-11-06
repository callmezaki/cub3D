/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 00:46:37 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/06 21:28:10 by sgmira           ###   ########.fr       */
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
