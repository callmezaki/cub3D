/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_parse_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 03:34:38 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/06 03:35:14 by zait-sli         ###   ########.fr       */
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
	if (c == 2)
		return (1);
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

void	check_compl(char **ss, t_color *col, char	**sp, char	*t)
{
	ss = ft_split(sp[1], ',');
	col->r = ft_atoi(ss[0]);
	col->g = ft_atoi(ss[1]);
	col->b = ft_atoi(ss[2]);
	free_tab(ss);
	free_tab(sp);
	check_color_range(*col);
	free(t);
}
