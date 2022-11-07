/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 04:46:56 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/07 01:19:13 by sgmira           ###   ########.fr       */
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
		printf("\n");
	else if (type == 9)
		printf("\n");
	else if (type == 10)
		printf("\n");
	exit_n_free(data, 1);
}

void	parse_walls(t_data *data, char **args)
{
	data->i = txtr_error(args, "NO");
	if (data->i < 0)
		exit_n_free(data, 1);
	check_space(args[data->i], data);
	data->no = ft_strdup(ft_strchr(args[data->i], '.'));
	check_path(data->no, data);
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

void	else_free(char	*tmp, char	**t)
{
	free(tmp);
	free_tab(t);
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

void	init_vars(t_data *data)
{
	if (W_HEIGHT > 2000 || W_HEIGHT < 300 || W_WIDTH < 300 || W_WIDTH > 2000)
	{
		printf("Error in Window Dimentions\n");
		exit(1);
	}
	data->tile = W_HEIGHT / 90;
	data->rotation_speed = (3 * M_PI / 180);
	data->rays_degr = (FOV / 2) * (M_PI / 180);
	data->rays_inc = data->rays_degr / (W_WIDTH / 2);
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
		init_vars(data);
		get_data(fd, data);
		init_window(data);
		exit_n_free(data, 0);
	}
}
