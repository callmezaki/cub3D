/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 04:46:56 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/06 04:56:32 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "cub3d.h"

#include <stdio.h>
#include <fcntl.h>
#include <mlx.h>
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
	if (i == 7)
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

int txtr_error(char **args, char *key)
{
	int	i;

	i = search_indx(args, key);
	if (i < 0)
		write(2, "Texture_ERROR!\n", 16);
	return (i);
}

void	parse_walls(t_data *data, char **args)
{
	int	i;

	i = txtr_error(args, "NO");
	if (i < 0)
		exit_n_free(data, 1);
	check_space(args[i], data);
	data->no = ft_strdup(ft_strchr(args[i], '.'));
	check_path(data->no, data);
	i = txtr_error(args, "DO");
	if (i < 0)
		exit_n_free(data, 1);
	check_space(args[i], data);
	data->doo = ft_strdup(ft_strchr(args[i], '.'));
	check_path(data->no, data);
	i = txtr_error(args, "SO");
	if (i < 0)
		exit_n_free(data, 1);
	check_space(args[i], data);
	data->so = ft_strdup(ft_strchr(args[i], '.'));
	check_path(data->so, data);
	i = txtr_error(args, "WE");
	if (i < 0)
		exit_n_free(data, 1);
	check_space(args[i], data);
	data->we = ft_strdup(ft_strchr(args[i], '.'));
	check_path(data->we, data);
	i = txtr_error(args, "EA");
	if (i < 0)
		exit_n_free(data, 1);
	check_space(args[i], data);
	data->ea = ft_strdup(ft_strchr(args[i], '.'));
	check_path(data->ea, data);
}

int check_duplicates(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		j = i + 1;
		while (str[j])
		{
			if (str[j] == str[i])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_assets(char **s)
{
	int		i;
	int		j;
	char	*str;
	char	*tmp;
	char	**t;

	str = ft_strdup("");
	tmp = ft_strdup("");
	i = 0;
	j = 0;
	while (s[i] && i < 7)
	{
		t = ft_split(s[i], ' ');
		if (t[0][0] && (!ft_strcmp(t[0], "NO") || !ft_strcmp(t[0], "SO")
			|| !ft_strcmp(t[0], "WE") || !ft_strcmp(t[0], "EA")
			|| !ft_strcmp(t[0], "C") || !ft_strcmp(t[0], "F")
			|| !ft_strcmp(t[0], "DO")))
		{
			tmp[0] = s[i][0];
			str = ft_strjoin_2(str, tmp);
			j++;
		}
		else
		{
			free(tmp);
			break ;
		}
		if (t[0][0])
			free_tab(t);
		i++;
	}
	if (!check_duplicates(str))
	{
		free(str);
		return (0);
	}
	free(str);
	return (1);
}

void get_player_data(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 1;
		while (data->map[i][j])
		{
			if (check_player(data->map[i][j]))
			{
				data->player.facing = data->map[i][j];
				data->player.x = (j * Z) + (Z / 2);
				data->player.y = (i * Z) + (Z / 2);
				if (data->player.facing == 'N')
					data->player.teta = 3 * M_PI / 2;
				else if (data->player.facing == 'S')
					data->player.teta = M_PI / 2;
				else if (data->player.facing == 'E')
					data->player.teta = 2 * M_PI;
				else if (data->player.facing == 'W')
					data->player.teta = M_PI;
				break ;
			}
			j++;
		}
		i++;
	}
}

void	parse_data(t_data *data,char *temp)
{
	char	**s;

	s = ft_split(temp, '\n');
	if (check_assets(s))
	{	
		free_tab(s);
		puts("FAIL");
		exit_n_free(data, 1);
	}
	parse_walls(data, s);
	get_colors(data, s);
	temp = intial_map_check(temp, s, data);
	free_tab(s);
	data->map = ft_split(temp, '\n');
	check_map(data->map, data);
	get_player_data(data);
	data->map_height = tab_len(data->map);
}

void	get_data(int fd, t_data *data)
{
	char	*str;
	char	*temp;
	int		i;

	i = 0;
	str = malloc(1);
	str[0] = '\0';
	temp = str;
	while (str)
	{
		str = get_next_line(fd);
		if (str)
		{
			if (i < 8)
			{
				if (ft_trima(&str, i))
				{
					str = ft_strjoin_2(str, "\n");
					i++;
				}
			}
			temp = ft_strjoin_2(temp, str);
			free(str);
		}
	}
	parse_data(data, temp);
	// if (temp)
	// 	free(temp);
}

void	f(void)
{
	printf("\n\n\n_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n\n\n");
	system("leaks cub3d");
}

void	exit_n_free(t_data *data, int t)
{
	(void)data;
	free(data->no);
	free(data->ea);
	free(data->we);
	free(data->so);
	free(data->doo);
	free_tab(data->map);
	free(data);
	exit(t);
}

int	main(int ac, char **av)
{
	atexit(f);
	t_data	*data;
	int		fd;
	char	*t;

	if (ac != 2)
		return (printf("Invalid Args\n"));
	data = malloc(sizeof(t_data));
	t = get_ext(av[1]);
	if (!ft_check_exten(t))
	{
		free(t);
		return (printf("Invalid Extention\n"));
	}
	free(t);
	fd = open(av[1], O_RDONLY);
	if (fd > 0)
	{
		get_data(fd, data);
		data->an = 0;
		init_window(data);
		exit_n_free(data, 0);
	}
}
