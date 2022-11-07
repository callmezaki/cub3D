/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 00:37:28 by sgmira            #+#    #+#             */
/*   Updated: 2022/11/07 03:16:18 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd("Floor/Ceiling colors range is wrong\n", 2);
	exit(1);
}

void	if_free(char	*str)
{
	if (str)
		free(str);
}
