/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 04:46:56 by zait-sli          #+#    #+#             */
/*   Updated: 2022/09/19 18:50:29 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
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

int ft_trima(char **a)
{
	char *t = *a;
	t = ft_strtrim(t, " \t");
	if(t)
	{
		*a = t;
		return(1);
	}
	else
		return(0);
		
}

void parse_data(t_data data,char *temp)
{
	
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
		if (str && ft_strcmp(str,"\n"))
		{
			if (i < 6)
				i+=ft_trima(&temp);
			temp = ft_strjoin(temp,str);
			free(str);
		}
	}
	printf("%s",temp);
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
	get_data(fd,data);
}
