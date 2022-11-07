/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 04:46:56 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/07 23:07:00 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_msg(t_data *data, int type)
{
	printf("Error\n");
	if (type == 0)
		ft_putstr_fd("Window dimmentions too big/small\n", 2);
	else if (type == 1)
		ft_putstr_fd("Map assets\n", 2);
	else if (type == 2)
		ft_putstr_fd("Texture not working\n", 2);
	else if (type == 3)
		ft_putstr_fd("Floor/Ceiling colors not working\n", 2);
	else if (type == 4)
		ft_putstr_fd("Map components are not valid\n", 2);
	else if (type == 5)
		ft_putstr_fd("Texure Path is not accessible\n", 2);
	else if (type == 6)
		ft_putstr_fd("Texure File is empty/not valid\n", 2);
	else if (type == 7)
		ft_putstr_fd("Invalid arguments\n", 2);
	else if (type == 8)
		ft_putstr_fd("Map file Path is not accessible\n", 2);
	else if (type == 9)
		ft_putstr_fd("Map extention is invalid\n", 2);
	exit_n_free(data, 1);
}

void	parse_walls_2(t_data *data, char **args)
{
	data->i = txtr_error(args, "WE");
	if (data->i < 0)
		exit_n_free(data, 1);
	check_space(args[data->i], data);
	if (ft_strchr(args[data->i], '.'))
		data->we = ft_strdup(ft_strchr(args[data->i], '.'));
	else
		error_msg(data, 1);
	check_path(data->we, data);
	data->i = txtr_error(args, "EA");
	if (data->i < 0)
		exit_n_free(data, 1);
	check_space(args[data->i], data);
	if (ft_strchr(args[data->i], '.'))
		data->ea = ft_strdup(ft_strchr(args[data->i], '.'));
	else
		error_msg(data, 1);
	check_path(data->ea, data);
}

void	parse_walls(t_data *data, char **args)
{
	data->i = txtr_error(args, "NO");
	if (data->i < 0)
		exit_n_free(data, 1);
	check_space(args[data->i], data);
	if (ft_strchr(args[data->i], '.'))
		data->no = ft_strdup(ft_strchr(args[data->i], '.'));
	else
		error_msg(data, 1);
	check_path(data->no, data);
	data->i = txtr_error(args, "SO");
	if (data->i < 0)
		exit_n_free(data, 1);
	check_space(args[data->i], data);
	if (ft_strchr(args[data->i], '.'))
		data->so = ft_strdup(ft_strchr(args[data->i], '.'));
	else
		error_msg(data, 1);
	check_path(data->so, data);
	parse_walls_2(data, args);
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
	if (ac != 2 || !data)
		error_msg(data, 7);
	t = get_ext(av[1]);
	check_path_2(av[1], data);
	if (!ft_check_exten(t))
	{
		free(t);
		error_msg(data, 9);
	}
	free(t);
	fd = open(av[1], O_RDONLY);
	if (fd > 0)
	{
		init_vars(data);
		get_data(fd, data);
		init_window(data);
		exit_n_free(data, 0);
	}
	return (0);
}
