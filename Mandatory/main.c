/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 04:46:56 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/03 01:08:08 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_walls(t_data *data, char **args)
{
	data->i = txtr_error(args, "NO");
	if (data->i < 0)
		exit_n_free(data, 1);
	check_space(args[data->i], data);
	data->NO = ft_strdup(ft_strchr(args[data->i], '.'));
	check_path(data->NO, data);
	data->i = txtr_error(args, "SO");
	if (data->i < 0)
		exit_n_free(data, 1);
	check_space(args[data->i], data);
	data->SO = ft_strdup(ft_strchr(args[data->i], '.'));
	check_path(data->SO, data);
	data->i = txtr_error(args, "WE");
	if (data->i < 0)
		exit_n_free(data, 1);
	check_space(args[data->i], data);
	data->WE = ft_strdup(ft_strchr(args[data->i], '.'));
	check_path(data->WE, data);
	data->i = txtr_error(args, "EA");
	if (data->i < 0)
		exit_n_free(data, 1);
	check_space(args[data->i], data);
	data->EA = ft_strdup(ft_strchr(args[data->i], '.'));
	check_path(data->EA, data);
}

void	else_free(char	*tmp, char	**t)
{
	free(tmp);
	free_tab(t);
}

void	if_free(char	*str)
{
	if (str)
		free(str);
}

void	get_data(int fd, t_data *data)
{
	char	*str;
	char	*temp;

	data->i = 0;
	str = malloc(1);
	str[0] = '\0';
	temp = str;
	while (str)
	{
		str = get_next_line(fd);
		if (str)
		{
			if (data->i < 7)
			{
				if (ft_trima(&str, data->i))
				{
					str = ft_strjoin_2(str, "\n");
					data->i++;
				}
			}
			temp = ft_strjoin_2(temp, str);
		}
		if_free(str);
	}
	parse_data(data, temp);
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		fd;
	char	*t;

	data = malloc(sizeof(t_data));
	if (ac != 2)
		return (printf("Invalid Args\n"));
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
		init_window(data);
		exit_n_free(data, 0);
	}
}
