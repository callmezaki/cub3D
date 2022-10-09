/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:54:52 by zait-sli          #+#    #+#             */
/*   Updated: 2022/10/09 15:11:01 by zait-sli         ###   ########.fr       */
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

# define W_height 1080
# define W_width 1920
# define Z 10
# define mini_cub 20
# define step 1
# define FOV 60
# define rotationspeed (3 * M_PI / 180)
# define D_rays (FOV / 2) * (M_PI / 180) 
# define rays W_width
# define inc_rays D_rays / (W_width / 2)

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


typedef struct s_point
{
	double y;
	double x;
} t_point;

typedef struct s_ray
{
	double x;
	double y;
	double distance;
	double alpha;
	int	h_or_v;
} t_ray;

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

typedef struct s_texture
{
	int *tab;
	int width;
	int height;
} t_texture;

typedef struct s_distance
{
	double distance;
	int h_or_v;
} t_distance;

typedef struct s_player
{
	char   facing;
	double x;
	double y;
	int    sides;
	int	   turndirection;
	int    walkdirection;
	double rotationangle;
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

typedef struct	s_txtr {
	t_texture north;
	t_texture south;
	t_texture east;
	t_texture west;
	t_texture door;
}	t_txtr;

typedef struct s_data
{
	char *NO;
	char *SO;
	char *WE;
	char *EA;
	char *DO;
	
	char **map;

	t_color F;
	t_color C;
	t_player player;
	t_window window;
	t_block  block;
	t_txtr txtr;
	t_ray  *r;
	t_distance distance;
	int map_width;
	int map_height;
	double map_x;
	double map_y;
	t_point centre_p;
} t_data;

char	*get_next_line(int fd);
void	my_mlx_pixel_put(t_window *data, int x, int y, int color);
void	init_window(t_data *data);
void    ft_block(t_data *data, double x, double y,int color);
int		check_player(char c);
int 	draw_minimap(t_data *data);
void	move_player(t_data *data);
void	rotate_player(t_data *data);
void	draw_walls(t_data *data);
void 	DDA(t_data *data, t_segment segment, int color);
void	claculate_rays(t_data *data);
void	draw_rays(t_segment *seg, t_data *data);
int		get_map_width(t_data *data, int y);
int		draw(t_data *data);
int		run(t_data *data);
int		draw_minimap_frame(t_data *data);
int		draw_minimap2(t_data *data);
void    ft_block2(t_data *data, double x, double y,int color);
void	DDA2(t_data *data, t_segment segment,int color);
void	draw_background(t_data *data);
int		get_color(char c);
void	get_texture(t_data *data);
double	h_distance(t_data *data, double beta);
double	v_distance(t_data *data, double beta);
void	claculate_rays(t_data *data);
void	best_distance(t_data *data, double beta);
double	normalize(double teta);
int		facing_right(double beta);
int		facing_down(double beta);
int		rgb_to_dec(t_color color);
void	move_map(t_data *data);
void	player_symbol(t_data *data, double x, double y,int color);


//parsing

int		check_cama(char *s);
void	check_color_range(t_color col);
t_color	check_color(char **s, int i);
void	get_colors(t_data *data, char **s);
int		search_indx(char **args, char *indx);
void check_map(char **s, t_data *data);
char *intial_map_check(char *s, char **t, t_data *data);
int    tab_len(char **str);
int check_valid(int c);
int check_player(char c);
void check_zero(char **s, int i, int j);
char  **ft_trima3(char **a);
int get_map_width(t_data *data, int y);
void exit_n_free(t_data *data, int t);
void	free_tab(char **tab);

#endif