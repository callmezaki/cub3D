/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 00:46:24 by sgmira            #+#    #+#             */
/*   Updated: 2022/11/03 00:46:45 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_ext(char *filename)
{
	int		i;
	char	*ext;

	i = ft_strlen(filename) - 4;
	ext = ft_strdup(&filename[i]);
	return (ext);
}

int	ft_check_exten(char *s)
{
	char	*t;

	t = get_ext(s);
	if (ft_strcmp(t, ".cub") == 0)
	{
		free(t);
		return (1);
	}
	else
	{
		free(t);
		return (0);
	}
}

int	ft_trima(char **a, int i)
{
	char	*t;

	t = *a;
	if (i == 6)
		t = ft_strtrim2_f(t, " \t\n");
	else
		t = ft_strtrim_f(t, " \t\n");
	*a = t;
	if (t[0])
		return (1);
	else
		return (0);
}

int	ft_trima2(char *a)
{
	char	*t;

	t = ft_strtrim(a, "  \t");
	if (t[0])
		return (1);
	else
		return (0);
	if (t)
		free(t);
}

char	**ft_trima3(char **a)
{
	int	i;

	i = 0;
	while (a[i])
	{
		a[i] = ft_strtrim2_f(a[i], "  \t");
		i++;
	}
	return (a);
}
