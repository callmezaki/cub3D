/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:54:52 by zait-sli          #+#    #+#             */
/*   Updated: 2022/09/19 22:29:09 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
#include <stdio.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"

typedef struct s_color
{
	int R;
	int G;
	int B;
} t_color;

typedef struct s_data
{
	char *NO;
	char *SO;
	char *WE;
	char *EA;
	
	char **map;

	t_color F;
	t_color C;
	
} t_data;

char	*get_next_line(int fd);


#endif