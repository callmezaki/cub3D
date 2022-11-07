/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 04:46:56 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/07 03:04:23 by sgmira           ###   ########.fr       */
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
	exit_n_free(data, 1);
}

void	get_player_data_calc(t_data *data, int i, int j)
{
	data->player.facing = data->map[i][j];
	data->player.x = (j * data->tile) + (data->tile / 2);
	data->player.y = (i * data->tile) + (data->tile / 2);
	if (data->player.facing == 'N')
		data->player.teta = 3 * M_PI / 2;
	else if (data->player.facing == 'S')
		data->player.teta = M_PI / 2;
	else if (data->player.facing == 'E')
		data->player.teta = 2 * M_PI;
	else if (data->player.facing == 'W')
		data->player.teta = M_PI;
}

void	parse_data(t_data *data, char *temp)
{
	char	**s;
	char	*t;

	s = ft_split(temp, '\n');
	if (check_assets(s, data))
	{	
		free_tab(s);
		puts("FAIL");
		exit_n_free(data, 1);
	}
	parse_walls(data, s);
	get_colors(data, s);
	t = intial_map_check(temp, s, data);
	free_tab(s);
	data->map = ft_split(t, '\n');
	check_map(data->map, data);
	get_player_data(data);
	data->map_height = tab_len(data->map);
	free(t);
}

void	f(void)
{
	printf("\n\n\n_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n\n\n");
	system("leaks cub3d");
}

void	init_vars(t_data *data)
{
	if (W_HEIGHT > 2000 || W_HEIGHT < 300 || W_WIDTH < 300 || W_WIDTH > 2000)
		error_msg(data, 0);
	data->an = 0;
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

	atexit(f);
	if (ac != 2)
		return (printf("Invalid Args\n"));
	t = get_ext(av[1]);
	if (!ft_check_exten(t))
	{
		free(t);
		return (printf("Invalid Extention\n"));
	}
	data = malloc(sizeof(t_data));
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
