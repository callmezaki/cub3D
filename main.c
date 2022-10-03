/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 04:46:56 by zait-sli          #+#    #+#             */
/*   Updated: 2022/10/03 01:33:02 by zait-sli         ###   ########.fr       */
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
	int i;
	char *ext;

	i = ft_strlen(filename) - 4;
	ext = ft_strdup(&filename[i]);
	return(ext);
}

int ft_check_exten(char *s)
{
	if(ft_strcmp(get_ext(s), ".cub") == 0)
		return 1;
	else
		return(0);
}

int ft_trima(char **a, int i)
{
	char *t = *a;
	if (i == 6)
		t = ft_strtrim2(t, " \t\n");
	else
		t = ft_strtrim(t, " \t\n");
	*a = t;
	if(t[0])
	{
		return(1);
	}
	else
		return(0);	
}

int ft_trima2(char *a)
{
	char *t;
	t = ft_strtrim(a, "  \t");
	if(t[0])
		return(1);
	else
		return(0);	
}

char  **ft_trima3(char **a)
{
	int i = 0;
	while(a[i])
	{
		a[i] = ft_strtrim2(a[i], "  \t");
		i++;
	}
	return(a);
}

int	search_indx(char **args, char *indx)
{
    int i;

    i = 0;
    if(ft_strlen(indx) == 2)
    {
        while(args[i])
        {
            if(args[i][0] == indx[0] && args[i][1] == indx[1])
                return(i);
            i++;    
        }
    }
    else if(ft_strlen(indx) == 1)
    {
        while(args[i])
        {
            if(args[i][0] == indx[0])
                return(i);
            i++;    
        }
    }
    return(-1);
}

int    tab_len(char **str)
{
    int i;

    i = 0;
    while(str[i])
        i++;
    return(i); 
}

void    check_space(char *s)
{
    if(tab_len(ft_split(s, ' ')) != 2)
    {
        printf("Error!\n");
        exit(1);
    }
}

void    check_path(char *data)
{
    if(access(data, F_OK | R_OK))
    {
        printf("Error! Path not accessible\n");
        exit(1);
    }
}

void    parse_walls(t_data *data, char **args)
{
    int i;
    i = search_indx(args, "NO");
	if (i < 0)
	{
		puts("Errrrrrrr");
		exit(1);
	}
    check_space(args[i]);
    data->NO = ft_strdup(ft_strchr(args[i], '.'));
    check_path(data->NO);
    i = search_indx(args, "SO");
	if (i < 0)
	{
		puts("Errrrrrrr");
		exit(1);
	}
    check_space(args[i]);
    data->SO = ft_strdup(ft_strchr(args[i], '.'));
    check_path(data->SO);
    i = search_indx(args, "WE");
	if (i < 0)
	{
		puts("Errrrrrrr");
		exit(1);
	}
    check_space(args[i]);
    data->WE = ft_strdup(ft_strchr(args[i], '.'));
    check_path(data->WE);
    i = search_indx(args, "EA");
	if (i < 0)
	{
		puts("Errrrrrrr");
		exit(1);
	}
    check_space(args[i]);
    data->EA = ft_strdup(ft_strchr(args[i], '.'));
    check_path(data->EA);
}

int check_duplicates(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(str[i])
	{
		j = i + 1;
		while(str[j])
		{
			if(str[j] == str[i])
				return(1);
			j++;
		}
		i++;
	}
	return(0);
}

int	check_assets(char **s)
{
	int i;
	int j;
	char *str;
	char *tmp;

	str = ft_strdup("");
	tmp = ft_strdup("");
	i = 0;
	j = 0;
	while(s[i])
	{
		if(!ft_strcmp(ft_split(s[i], ' ')[0], "NO") || !ft_strcmp(ft_split(s[i], ' ')[0], "SO")
			|| !ft_strcmp(ft_split(s[i], ' ')[0], "WE") || !ft_strcmp(ft_split(s[i], ' ')[0], "EA") 
			|| !ft_strcmp(ft_split(s[i], ' ')[0], "C") || !ft_strcmp(ft_split(s[i], ' ')[0], "F"))
		{
			tmp[0] = s[i][0];
			str = ft_strjoin(str, tmp);
			j++;
		}
		else
			break;
		i++;
	}
	if(!check_duplicates(str) && j == 6)
		return(0);
	return(1);
}

void get_player_data(t_data *data)
{
	int i = 0;
	int j = 0;
	while(data->map[i])
	{
		j = 1;
		while(data->map[i][j])
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
				break;
			}
			j++;
		}
		i++;
	}
}

void parse_data(t_data *data,char *temp)
{
	char **s = ft_split(temp,'\n');
	if(check_assets(s))
	{
		puts("FAIL");
		exit(1);
	}
	parse_walls(data,s);
	get_colors(data, s);
	temp = intial_map_check(temp, s);
	data->map = ft_split(temp,'\n');
	check_map(data->map);
	get_player_data(data);
	data->map_height = tab_len(data->map);
}

void get_data(int fd, t_data *data)
{
	char *str;
	char *temp;
	int i = 0;
	
	(void)data;
	
	str = malloc(1);
	str[0] = '\0';
	temp = str;
	while(str)
	{
		str = get_next_line(fd);
		if (str)
		{
			if (i < 7)
			{
				if (ft_trima(&str,i))
				{
					str = ft_strjoin(str,"\n");
					i++;
				}
			}
			temp = ft_strjoin(temp,str);
			free(str);
		}
	}
	parse_data(data,temp);
}

int main(int ac, char **av)
{
	t_data *data;
	data = malloc(sizeof(t_data));
	int fd;
	if (ac != 2)
		return(printf("Invalid Args\n"));
	if (!ft_check_exten(get_ext(av[1])))
		return(printf("Invalid Extention\n"));
	fd = open(av[1], O_RDONLY);
	if (fd > 0)
	{
		get_data(fd,data);
		init_window(data);
	}
}
