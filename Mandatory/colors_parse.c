/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 00:30:29 by zait-sli          #+#    #+#             */
/*   Updated: 2022/10/19 22:41:31 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_cama(char *s)
{
	int	i;
	int	c;
	int	len;

	i = -1;
	c = 0;
	len = ft_strlen(s);
	if (s[0] == ',' || s[len] == ',')
		return (0);
	else
	{
		while (s[++i] && s[i + 1])
		{
			if (s[i] == ',' && s[i + 1] == ',')
				return (0);
			if (s[i] == ',')
				c++;
		}
	}
	if (s[ft_strlen(s) - 1] == ',')
		c++;
	if (c == 2)
		return (1);
	else
		return (0);
}

void	check_color_range(t_color col)
{
	if (col.r <= 255 && col.r >= 0)
	{
		if (col.g <= 255 && col.g >= 0)
		{
			if (col.b <= 255 && col.b >= 0)
			{
				return ;
			}
		}
	}
	printf("Error\n");
	exit(1);
}

void	fill_col(char	**sp, t_color *col, char *t)
{
	char	**ss;

	ss = ft_split(sp[1], ',');
	col->r = ft_atoi(ss[0]);
	col->g = ft_atoi(ss[1]);
	col->b = ft_atoi(ss[2]);
	free_tab(ss);
	free_tab(sp);
	check_color_range(*col);
	free(t);
}

void	error_n_free(char **sp, char	*t)
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

t_color	check_color(char **s, int i)
{
	t_color	col;
	char	**sp;
	char	*t;
	int		j;

	j = -1;
	t = ft_strdup(s[i]);
	sp = ft_split(t, ' ');
	error_n_free2(sp, t);
	if (check_cama(sp[1]))
	{
		while (sp[1][++j])
		{
			if (!ft_isdigit(sp[1][j]) && sp[1][j] != ',')
			{
				free_tab(sp);
				printf("Error1\n");
				exit(1);
			}
		}
		fill_col(sp, &col, t);
	}
	else
	{
		free_tab(sp);
		free(t);
		printf("Error\n");
		exit(0);
	}
	return (col);
}

void	get_colors(t_data *data, char **s)
{
	int	i;

	i = search_indx(s, "F");
	if (i >= 0)
	{
		data->F = check_color(s, i);
		i = search_indx(s, "C");
		if (i >= 0)
		{
			data->C = check_color(s, i);
		}
		return ;
	}
	printf("Error8\n");
	exit(1);
}
