/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 00:49:21 by sgmira            #+#    #+#             */
/*   Updated: 2022/11/03 00:49:47 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	search_indx(char **args, char *indx)
{
	int	i;

	i = 0;
	if (ft_strlen(indx) == 2)
	{
		while (args[i])
		{
			if (args[i][0] == indx[0] && args[i][1] == indx[1])
				return (i);
			i++;
		}
	}
	else if (ft_strlen(indx) == 1)
	{
		while (args[i])
		{
			if (args[i][0] == indx[0])
				return (i);
			i++;
		}
	}
	return (-1);
}

int	tab_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	check_space(char *s, t_data *data)
{
	char	**t;

	t = ft_split(s, ' ');
	if (tab_len(t) != 2)
	{
		free_tab(t);
		printf("Error!\n");
		exit_n_free(data, 1);
	}
	free_tab(t);
}

void	check_path(char *d, t_data *data)
{
	if (access(d, F_OK | R_OK))
	{
		printf("Error! Path not accessible\n");
		exit_n_free(data, 1);
	}
}

int	txtr_error(char **args, char *key)
{
	int	i;

	i = search_indx(args, key);
	if (i < 0)
	{
		printf("%s\n", key);
		write(2, "Texture_ERROR!\n", 16);
	}
	return (i);
}
