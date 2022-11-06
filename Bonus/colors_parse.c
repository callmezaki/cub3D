/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 00:30:29 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/06 04:57:44 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	f_n_ex(char	**sp, char	*t)
{
	free_tab(sp);
	free(t);
	printf("Error\n");
	exit(0);
}

void	error_n_free2(char	**sp, char	*t)
{
	if (!sp[1] || sp[2])
	{
		if (sp[0])
			free_tab(sp);
		free(t);
		printf("Error0\n");
		exit(1);
	}
}

void	f_n_ex_2(char	**sp)
{
	free_tab(sp);
	printf("Error1\n");
	exit(1);
}

t_color	check_color(char **s, int i)
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
	error_n_free2(sp, t);
	if (check_cama(sp[1]))
	{
		while (sp[1][j])
		{
			if (!ft_isdigit(sp[1][j]) && sp[1][j] != ',')
				f_n_ex_2(sp);
			j++;
		}
		check_compl(ss, &col, sp, t);
	}
	else
		f_n_ex(sp, t);
	return (col);
}

void	get_colors(t_data *data, char **s)
{
	int	i;

	i = search_indx(s, "F");
	if (i >= 0)
	{
		data->f = check_color(s, i);
		i = search_indx(s, "C");
		if (i >= 0)
		{
			data->c = check_color(s, i);
		}
		return ;
	}
	printf("Error8\n");
	exit(1);
}
