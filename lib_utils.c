/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:52:55 by sgmira            #+#    #+#             */
/*   Updated: 2022/10/05 10:01:22 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strdup(const char *src, t_data *data)
{
	int		i;
	char	*dup;

	i = ft_strlen(src);
	dup = (char *)malloc(i + 1);
	if (dup == NULL)
		return (0);
	ft_addbackthegarbe(&data->trash, ft_newgarbage(dup));
	i = 0;
	while (src[i] != '\0')
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_substr(char const *s, unsigned int start, size_t len, t_data *data)
{
	size_t			x;
	size_t			xlen;
	char			*sub;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup("", data));
	xlen = ft_strlen(&s[start]);
	if (xlen >= len)
		xlen = len;
	sub = (char *)malloc(xlen + 1);
	if (!sub)
		return (NULL);
	ft_addbackthegarbe(&data->trash, ft_newgarbage(sub));
	x = 0;
	while (s[start] && x < len)
		sub[x++] = s[start++];
	sub[x] = '\0';
	return (sub);
}