/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:54:52 by zait-sli          #+#    #+#             */
/*   Updated: 2022/09/23 17:54:32 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
#include <stdio.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "libft/libft.h"
#include "mlx.h"

# define Z 20
# define step 3
// # define step 0.05

# define KEY_W 13 
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53
# define LEFT	123
# define RIGHT	124

typedef struct s_color
{
	int R;
	int G;
	int B;
} t_color;

typedef struct s_block
{
	double x0;
	double x1;
	double y0;
	double y1;

	int color;
} t_block;


typedef struct s_segment
{
	double x0;
	double x1;
	double y0;
	double y1;
} t_segment;

typedef struct s_player
{
	char   facing;
	double x;
	double y;
	int	   turndirection;
	int    walkdirection;
	double rotationangle;
	double movespeed;
	double rotationspeed;	
	double teta;
	t_segment seg;
	
} t_player;

typedef struct	s_window {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*mlx;
	void	*mlx_win;
}	t_window;

typedef struct s_data
{
	char *NO;
	char *SO;
	char *WE;
	char *EA;
	
	char **map;

	t_color F;
	t_color C;
	t_player player;
	t_window window;
	t_block  block;
} t_data;

char	*get_next_line(int fd);
void	my_mlx_pixel_put(t_window *data, int x, int y, int color);
void	init_window(t_data *data);
void    ft_block(t_window *data, t_block block);
int		check_player(char c);
int 	draw_minimap(t_data *data);
void	draw_player(t_data *data);
void 	DDA(t_data *data, t_segment segment);
#endif