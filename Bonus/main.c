/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 04:46:56 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/06 20:33:25 by zait-sli         ###   ########.fr       */
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

void parse_walls_2(t_data *data, char **args)
{
	data->i = txtr_error(args, "SO");
	if (data->i < 0)
		exit_n_free(data, 1);
	check_space(args[data->i], data);
	data->so = ft_strdup(ft_strchr(args[data->i], '.'));
	check_path(data->so, data);
	data->i = txtr_error(args, "WE");
	if (data->i < 0)
		exit_n_free(data, 1);
	check_space(args[data->i], data);
	data->we = ft_strdup(ft_strchr(args[data->i], '.'));
	check_path(data->we, data);
	data->i = txtr_error(args, "EA");
	if (data->i < 0)
		exit_n_free(data, 1);
	check_space(args[data->i], data);
	data->ea = ft_strdup(ft_strchr(args[data->i], '.'));
	check_path(data->ea, data);
}

void	parse_walls(t_data *data, char **args)
{
	data->i = txtr_error(args, "NO");
	if (data->i < 0)
		exit_n_free(data, 1);
	check_space(args[data->i], data);
	data->no = ft_strdup(ft_strchr(args[data->i], '.'));
	check_path(data->no, data);
	data->i = txtr_error(args, "DO");
	if (data->i < 0)
		exit_n_free(data, 1);
	check_space(args[data->i], data);
	data->doo = ft_strdup(ft_strchr(args[data->i], '.'));
	check_path(data->no, data);
	parse_walls_2(data, args);
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

char	*check_assets_loop(t_data *data, char **s, char	*str, char	**t)
{
	while (s[data->i] && data->i < 7)
	{
		t = ft_split(s[data->i], ' ');
		if (t[0][0] && (!ft_strcmp(t[0], "NO") || !ft_strcmp(t[0], "SO")
			|| !ft_strcmp(t[0], "WE") || !ft_strcmp(t[0], "EA")
			|| !ft_strcmp(t[0], "C") || !ft_strcmp(t[0], "F")
			|| !ft_strcmp(t[0], "DO")))
		{
			data->tmp[0] = s[data->i][0];
			str = ft_strjoin_2(str, data->tmp);
			data->j++;
		}
		else
		{
			free(data->tmp);
			break ;
		}
		if (t[0][0])
			free_tab(t);
		data->i++;
	}
	return (str);
}

int	check_assets(char **s, t_data *data)
{
	char	*str;
	char	**t;

	t = NULL;
	str = ft_strdup("");
	data->tmp = ft_strdup("");
	data->i = 0;
	data->j = 0;
	str = check_assets_loop(data, s, str, t);
	if (!check_duplicates(str))
	{
		free(str);
		return (0);
	}
	free(str);
	return (1);
}

void	get_player_data_calc(t_data *data, int	i, int	j)
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
				get_player_data_calc(data, i, j);
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
	if (check_assets(s, data))
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

char	*get_data_loop(t_data *data, char	*str, int fd, char	*temp)
{
	while (str)
	{
		str = get_next_line(fd);
		if (str)
		{
			if (data->i < 8)
			{
				if (ft_trima(&str, data->i))
				{
					str = ft_strjoin_2(str, "\n");
					data->i++;
				}
			}
			temp = ft_strjoin_2(temp, str);
			free(str);
		}
	}
	return (temp);
}

void	get_data(int fd, t_data *data)
{
	char	*str;
	char	*temp;

	data->i = 0;
	str = malloc(1);
	str[0] = '\0';
	temp = str;
	temp = get_data_loop(data, str, fd, temp);
	parse_data(data, temp);
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

void	init_vars(t_data *data)
{
	if (W_HEIGHT > 2000 || W_HEIGHT < 300 || W_WIDTH < 300 || W_WIDTH > 2000)
	{
		printf("Error in Window Dimentions\n");
		exit(1);
	}
	data->an = 0;
	data->rotation_speed = (3 * M_PI / 180);
	data->rays_degr = (FOV / 2) * (M_PI / 180);
	data->rays_inc = data->rays_degr / (W_WIDTH / 2);
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		fd;
	char	*t;

	atexit(f);
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
		init_vars(data);
		init_window(data);
		exit_n_free(data, 0);
	}
}
