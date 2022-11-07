/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 00:30:29 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/07 03:10:18 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_cama(char *s)
{
	int	i;
	int	c;
	int	len;

	i = 0;
	c = 0;
	len = ft_strlen(s);
	if (s[0] == ',' || s[len] == ',')
		return (0);
	else
	{
		while (s[i] && s[i + 1])
		{
			if (s[i] == ',' && s[i + 1] == ',')
				return (0);
			if (s[i] == ',')
				c++;
			i++;
		}
	}
	if (s[ft_strlen(s) - 1] == ',')
		c++;
	return (1);
}

void	f_n_ex(char	**sp, char	*t, t_data *data)
{
	free_tab(sp);
	free(t);
	error_msg(data, 3);
}

void	f_n_ex_2(char	**sp, t_data *data)
{
	free_tab(sp);
	error_msg(data, 3);
}

t_color	check_color(char **s, int i, t_data *data)
{
	t_color	col;
	char	**sp;
	char	*t;
	int		j;

	j = -1;
	t = ft_strdup(s[i]);
	sp = ft_split(t, ' ');
	col.b = 0;
	error_n_free2(sp, t, data);
	if (check_cama(sp[1]))
	{
		while (sp[1][++j])
		{
			if (!ft_isdigit(sp[1][j]) && sp[1][j] != ',')
				f_n_ex_2(sp, data);
		}
		fill_col(sp, &col, t);
	}
	else
		f_n_ex(sp, t, data);
	return (col);
}

void	get_colors(t_data *data, char **s)
{
	int	i;

	i = search_indx(s, "F");
	if (i >= 0)
	{
		data->f = check_color(s, i, data);
		i = search_indx(s, "C");
		if (i >= 0)
			data->c = check_color(s, i, data);
		return ;
	}
	error_msg(data, 3);
}
