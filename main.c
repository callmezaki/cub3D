/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 04:46:56 by zait-sli          #+#    #+#             */
/*   Updated: 2022/09/26 17:33:50 by zait-sli         ###   ########.fr       */
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

int    search_indx(char **args, char *indx)
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

int check_cama(char *s)
{
	int i = 0;
	int c = 0;
	int len = ft_strlen(s);
	if (s[0] == ',' || s[len] == ',')
		return(0);
	else
	{
		while(s[i] && s[i+1])
		{
			if(s[i] == ',' && s[i+1] == ',')
				return(0);
			if (s[i] == ',')
				c++;
			i++;
		}
	}
	if (c == 2)
		return(1);
	else
		return(0);
}

void check_color_range(t_data *d)
{
	if (d->F.R <= 255 && d->F.R >= 0)
	{
		if (d->F.G <= 255 && d->F.G >= 0)
		{
			if (d->F.B <= 255 && d->F.B >= 0)
			{
				if (d->C.R <= 255 && d->C.R >= 0)
				{
					if (d->C.G <= 255 && d->C.G >= 0)
					{
						if (d->C.B <= 255 && d->C.B >= 0)
						{
							return ;
						}
					}
				}
			}
		}
		
	}
	printf("Error\n");
	exit(1);
}

void	get_colors(t_data *data, char **s)
{
	(void)data;
	char **sp;
	char **ss;
	int i = search_indx(s, "F");
	int j = 0;
	if (i > 0)
	{
		char *t = ft_strdup(s[i]);
		sp = ft_split(t,' ');
		if (!sp[1] || sp[2])
		{
			printf("Error\n");
			exit(1);
		}
		if (check_cama(sp[1]))
		{
			while(sp[1][j])
			{
				if (!ft_isdigit(sp[1][j]) && sp[1][j] != ',')
				{
					printf("Error\n");
					exit(1);
				}
				j++;
			}
			ss = ft_split(sp[1],',');
			data->F.R = ft_atoi(ss[0]);
			data->F.G = ft_atoi(ss[1]);
			data->F.B = ft_atoi(ss[2]);
			i = search_indx(s, "C");
			free(t);
			if (i > 0)
			{
				t = ft_strdup(s[i]);
				sp = ft_split(t,' ');
				if (!sp[1] || sp[2])
				{
					printf("Error\n");
					exit(1);
				}
				if (check_cama(sp[1]))
				{
					j = 0;
					while(sp[1][j])
					{
						if (!ft_isdigit(sp[1][j]) && sp[1][j] != ',')
						{
							printf("Error\n");
							exit(1);
						}
						j++;
					}
					ss = ft_split(sp[1],',');
					data->C.R = ft_atoi(ss[0]);
					data->C.G = ft_atoi(ss[1]);
					data->C.B = ft_atoi(ss[2]);
					
					check_color_range(data);
					return ;
				}
			}
		}
	}
	printf("Error\n");
	exit(1);
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

char *intial_map_check(char *s, char **t)
{
	int i = 0;
	int len = 0;
	char *a;
	char *b;
	int p_count = 0;

	while(i< 6)
	{
		len+= ft_strlen(t[i]);
		i++;
	}
	s = ft_strdup(&s[len + i]);
	i = 0;
	while(s[i] && s[i + 1])
	{
		if((s[i] == '\n' && s[i + 1] == '\n'))
		{
			break ;
		}
		if (check_player(s[i]))
			p_count++;
		i++;
	}
	if (p_count > 1 || p_count == 0)
	{
		printf("P Error\n");
		exit(0);
	}
	while(s[i])
	{
		if (s[i] != ' ' && s[i] != '\n' && s[i] != '\t' && s[i] != '1')
		{
			printf("%c\n",s[i]);
			printf("Errrrroooor\n");
			exit(1);
		}
		i++;
	}
	t = ft_split(s, '\n');
	len = 0;
	i = 1;
	while(t[i])
	{
		a = ft_strtrim(t[i]," ");
		b = ft_strtrim(t[i-1]," ");
		if (!a[0] && b[0])
		{
			len++;
		}
		i++;
	}
	if (len > 1)
	{
		printf("Errrrroooor7\n");
		exit(1);
	}
	s = ft_strtrim2(s," \n\t");
	return (s);
}

int check_valid(int c)
{
	if(c == '1' || c == '0' || c == 'N' || c == 'W' || c == 'E' || c == 'S' || c == ' ')
		return(1);
	return(0);
}

int check_player(char c)
{
	if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
		return(1);
	return(0);
}

void check_zero(char **s, int i, int j)
{
	if (s[i - 1][j] == '1' || s[i - 1][j] == '0' || check_player(s[i - 1][j]))
	{
		if (s[i + 1][j] == '1' || s[i + 1][j] == '0' || check_player(s[i + 1][j]))
		{
			if (s[i][j+1] == '1' || s[i][j+1] == '0' || check_player(s[i][j+1]))
			{
				if (s[i][j-1] == '1' || s[i][j-1] == '0' || check_player(s[i][j-1]))
					return ;
			}
		}
		
	}
	printf("Error000\n");
	exit(1);
}

void check_map(char **s)
{
	int i = 0;
	int j = 0;
	int len = tab_len(s) -1;
	
	s = ft_trima3(s);
	while(s[i])
	{
		j = 0;
		while(s[i][j])
		{
			if (!check_valid(s[i][j]))
			{
				printf("Erroop0\n");
				exit(1);
			}
			j++;
		}
		i++;
	}
	i = 0;
	j = 0;
	while(s[0][j])
	{
		if (s[0][j] != ' ' && s[0][j] != '1')
		{
			printf("Erroop1\n");
			exit(1);
		}
		j++;
	}
	j = 0;
	while(s[len][j])
	{
		if (s[len][j] != ' ' && s[len][j] != '1')
		{
			printf("Erroop2\n");
			exit(1);
		}
		j++;
	}
	j = 0;
	while(s[i])
	{
		if ((s[i][0] != ' ' && s[i][0] != '1'))
		{
			printf("Erroop3\n");
			exit(1);
		}
		i++;
	}
	i = 0;
	while(s[i])
	{
		if ((s[i][ft_strlen(s[i]) - 1] != ' ' && s[i][ft_strlen(s[i]) - 1] != '1'))
		{
			printf("Erroop4\n");
			exit(1);
		}
		i++;
	}
	i = 1;
	while(s[i + 1])
	{
		j = 1;
		while(s[i][j])
		{
			if (s[i][j] == '0' || check_player(s[i][j]))
				check_zero(s, i, j);
			j++;
		}
		i++;
	}
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
		if(s[i][0] == 'N' || s[i][0] == 'S' || s[i][0] == 'W'
			|| s[i][0] == 'E' || s[i][0] == 'C' || s[i][0] == 'F')
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

int get_map_width(t_data *data, int y)
{
	if (y <= data->map_height)
	{
		return(ft_strlen(data->map[y]));
	}
	return(-1);
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
