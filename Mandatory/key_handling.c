/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 00:02:45 by sgmira            #+#    #+#             */
/*   Updated: 2022/11/06 19:55:12 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	you_quit(void)
{
	write(1, "-------You Quit!-------\n", 25);
	exit(EXIT_SUCCESS);
}

void	key_press_cond(int key, t_data *data)
{
	if (key == KEY_A)
	{
		data->player.sides = 1;
		data->player.walkdirection = -1;
	}
	else if (key == KEY_D)
	{
		data->player.sides = 1;
		data->player.walkdirection = 1;
	}
	else if (key == LEFT)
		data->player.turndirection = -1;
	else if (key == RIGHT)
		data->player.turndirection = 1;
	else if (key == KEY_ESC)
		exit_n_free(data, 0);
}

int	key_press(int key, t_data *data)
{
	if (key == KEY_W)
	{
		data->player.sides = 0;
		data->player.walkdirection = 1;
	}
	else if (key == KEY_S)
	{
		data->player.sides = 0;
		data->player.walkdirection = -1;
	}
	key_press_cond(key, data);
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == KEY_W)
		data->player.walkdirection = 0;
	else if (key == KEY_S)
		data->player.walkdirection = 0;
	if (key == KEY_A)
		data->player.walkdirection = 0;
	else if (key == KEY_D)
		data->player.walkdirection = 0;
	else if (key == LEFT)
		data->player.turndirection = 0;
	else if (key == RIGHT)
		data->player.turndirection = 0;
	return (0);
}

// int	check_assets(char **s, char	*str, char	*tmp, char	**t, t_data *data)
// {
// 	data->i = 0;
// 	data->j = 0;
// 	while (s[data->i] && data->i < 7)
// 	{
// 		t = ft_split(s[data->i], ' ');
// 		if (!ft_strcmp(t[0], "NO") || !ft_strcmp(t[0], "SO")
// 			|| !ft_strcmp(t[0], "WE") || !ft_strcmp(t[0], "EA")
// 			|| !ft_strcmp(t[0], "C") || !ft_strcmp(t[0], "F"))
// 		{
// 			tmp[0] = s[data->i][0];
// 			str = ft_strjoin_2(str, tmp);
// 			data->j++;
// 		}
// 		else
// 		{
// 			else_free(tmp, t);
// 			break ;
// 		}
// 		free_tab(t);
// 		data->i++;
// 	}
// 	if (!check_free(str))
// 		return (0);
// 	free(str);
// 	return (1);
// }

char	*check_assets_loop(t_data *data, char **s, char	*str, char	**t)
{
	while (s[data->i] && data->i < 7)
	{
		t = ft_split(s[data->i], ' ');
		if (t[0][0] && (!ft_strcmp(t[0], "NO") || !ft_strcmp(t[0], "SO")
			|| !ft_strcmp(t[0], "WE") || !ft_strcmp(t[0], "EA")
			|| !ft_strcmp(t[0], "C") || !ft_strcmp(t[0], "F")))
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
