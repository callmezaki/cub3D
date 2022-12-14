/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 03:47:04 by zait-sli          #+#    #+#             */
/*   Updated: 2022/10/05 14:20:52 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

#include<stdlib.h>

static int	words_count(char *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		if (i == 0 || s[i - 1] == c)
		{
			if (s[i] != c && s[i] != '\0')
				words++;
		}
		i++;
	}
	return (words);
}

static void	move_word(char *from, char *to, int start, int j)
{
	int	a;

	a = 0;
	while (j > 0)
	{
		to[a] = from[start];
		a++;
		start++;
		j--;
	}
	to[a] = '\0';
}

static void	ft_free(char **p, int a)
{
	while (a >= 0)
		free(p[--a]);
	free(p);
}

static void	ft_lastpart(char **p, char const *s, char c)
{
	int		i;
	int		len;
	int		a;

	i = 0;
	len = 0;
	a = 0;
	while (s[i])
	{
		len = 0;
		while (s[i] == c)
			i++;
		while (s[i + len] != c && s[i + len] != '\0')
			len++;
		if (len != 0)
		{
			p[a] = (char *)malloc(len + 1);
			if (p[a] == NULL)
				ft_free(p, a);
			move_word((char *)s, p[a], i, len);
			a++;
		}
		i = i + len;
	}
}

char	**ft_split(char const *s, char c)
{
	int		len;
	char	**p;

	if (!s)
		return (NULL);
	len = words_count((char *)s, c);
	p = (char **)malloc(sizeof(char *) * (words_count((char *)s, c) + 1));
	if (p == NULL)
		return (NULL);
	ft_lastpart(p, s, c);
	p[len] = NULL;
	return (p);
}
