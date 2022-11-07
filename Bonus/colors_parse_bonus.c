/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_parse_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 00:30:29 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/07 19:47:52 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	f_n_ex(char	**sp, char	*t, t_data *data)
{
	free_tab(sp);
	free(t);
	error_msg(data, 3);
}

void	error_n_free2(char	**sp, char	*t, t_data *data)
{
	if (!sp[1] || sp[2])
	{
		if (sp[0])
			free_tab(sp);
		free(t);
		error_msg(data, 3);
	}
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
	char	**ss;
	char	*t;
	int		j;

	j = 0;
	t = ft_strdup(s[i]);
	sp = ft_split(t, ' ');
	ss = NULL;
	col.b = 0;
	error_n_free2(sp, t, data);
	if (check_cama(sp[1]))
	{
		while (sp[1][j])
		{
			if (!ft_isdigit(sp[1][j]) && sp[1][j] != ',')
				f_n_ex_2(sp, data);
			j++;
		}
		check_compl(ss, &col, sp, t);
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
