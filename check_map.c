/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 00:46:37 by zait-sli          #+#    #+#             */
/*   Updated: 2022/10/03 01:01:23 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_valid_chars(char **s)
{
	int i;
	int j;
	
	i = 0;
	while(s[i])
	{
		j = 0;
		while(s[i][j])
		{
			if (!check_valid(s[i][j]))
				return(0); 
			j++;
		}
		i++;
	}
	return(1);
}

int  check_line(char **s)
{
	int i;
	int j;
	int len;
	int t;
	
	i = 0;
	j = 0;
	len = tab_len(s) -1;
	while(s[0][j])
	{
		if (s[0][j] != ' ' && s[0][j] != '1')
			return(0);
		j++;
	}
	j = 0;
	while(s[len][j])
	{
		if (s[len][j] != ' ' && s[len][j] != '1')
			return(0);
		j++;
	}
	while(s[i])
	{
		t = ft_strlen(s[i]) - 1;
		if ((s[i][t] != ' ' && s[i][t] != '1') || (s[i][0] != ' ' && s[i][0] != '1'))
			return(0);
		i++;
	}
	return(1);
}

void check_map(char **s)
{
	int i;
	int j;
	int check;
	
	s = ft_trima3(s);
	check = check_valid_chars(s);
	check = check_line(s);
	i = 1;
	while(s[i + 1] && check)
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
	if (!check)
	{
		printf("Error check_map\n");
		exit(1);
	}
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