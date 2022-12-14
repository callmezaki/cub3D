/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:01:45 by zait-sli          #+#    #+#             */
/*   Updated: 2022/10/05 14:23:02 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		start;
	size_t		end;
	char		*s;

	s = 0;
	if (s1 != 0 && set != 0)
	{
		start = 0;
		end = ft_strlen(s1);
		while (s1[start] && ft_strchr(set, s1[start]))
			start++;
		while (s1[end - 1] && ft_strchr(set, s1[end - 1]) && end > start)
			end--;
		s = (char *)malloc(sizeof(char) * (end - start + 1));
		if (s)
			ft_strlcpy(s, &s1[start], end - start + 1);
	}
	return (s);
}

char	*ft_strtrim2(char const *s1, char const *set)
{
	size_t		start;
	size_t		end;
	char		*s;

	s = 0;
	if (s1 != 0 && set != 0)
	{
		start = 0;
		end = ft_strlen(s1);
		while (s1[end - 1] && ft_strchr(set, s1[end - 1]) && end > start)
			end--;
		s = (char *)malloc(sizeof(char) * (end - start + 1));
		if (s)
			ft_strlcpy(s, &s1[start], end - start + 1);
	}
	return (s);
}

char	*ft_strtrim_f(char const *s1, char const *set)
{
	size_t		start;
	size_t		end;
	char		*s;

	s = 0;
	if (s1 != 0 && set != 0)
	{
		start = 0;
		end = ft_strlen(s1);
		while (s1[start] && ft_strchr(set, s1[start]))
			start++;
		while (s1[end - 1] && ft_strchr(set, s1[end - 1]) && end > start)
			end--;
		s = (char *)malloc(sizeof(char) * (end - start + 1));
		if (s)
			ft_strlcpy(s, &s1[start], end - start + 1);
	}
	free((char *)s1);
	return (s);
}

char	*ft_strtrim2_f(char const *s1, char const *set)
{
	size_t		start;
	size_t		end;
	char		*s;

	s = 0;
	if (s1 != 0 && set != 0)
	{
		start = 0;
		end = ft_strlen(s1);
		while (s1[end - 1] && ft_strchr(set, s1[end - 1]) && end > start)
			end--;
		s = (char *)malloc(sizeof(char) * (end - start + 1));
		if (s)
			ft_strlcpy(s, &s1[start], end - start + 1);
	}
	free((char *)s1);
	return (s);
}
