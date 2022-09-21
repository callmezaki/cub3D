/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:54:52 by zait-sli          #+#    #+#             */
/*   Updated: 2022/09/21 17:30:24 by zait-sli         ###   ########.fr       */
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
#include "mlx.h"

typedef struct s_color
{
	int R;
	int G;
	int B;
} t_color;

typedef struct s_block
{
	int x0;
	int x1;
	int y0;
	int y1;

	int color;
} t_block;

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

typedef struct	s_window {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_window;

char	*get_next_line(int fd);
void	my_mlx_pixel_put(t_window *data, int x, int y, int color);
void	init_window(t_data *data);
void    ft_block(t_window *data, t_block block);
int		check_player(char c);
void	draw_minimap(t_window *win ,t_data *data);
#endif