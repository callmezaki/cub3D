/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:54:52 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/07 00:34:41 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "libft/libft.h"
# include "mlx.h"

# define W_HEIGHT 1080
# define W_WIDTH 1920
# define MINI_CUB 20
# define STEP 1.5
# define FOV 60
# define RAYS W_WIDTH

# define KEY_W 13 
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53
# define LEFT	123
# define RIGHT	124

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_point
{
	double	y;
	double	x;
}	t_point;

typedef struct s_ray
{
	double	x;
	double	y;
	double	distance;
	double	alpha;
	int		h_or_v;
}	t_ray;

typedef struct s_block
{
	double	x0;
	double	x1;
	double	y0;
	double	y1;
	int		color;
}	t_block;

typedef struct s_segment
{
	double	x0;
	double	x1;
	double	y0;
	double	y1;
}	t_segment;

typedef struct s_texture
{
	int	*tab;
	int	width;
	int	height;
}	t_texture;

typedef struct s_distance
{
	double	distance;
	int		h_or_v;
}	t_distance;

typedef struct s_player
{
	char		facing;
	double		x;
	double		y;
	int			sides;
	int			turndirection;
	int			walkdirection;
	double		rotationangle;
	double		teta;
	t_segment	seg;

}	t_player;

typedef struct s_window
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*mlx;
	void	*mlx_win;
}	t_window;

typedef struct s_txtr
{
	t_texture	north;
	t_texture	south;
	t_texture	east;
	t_texture	west;
}	t_txtr;

typedef struct s_dwvars
{
	int			i;
	int			j;
	t_point		txtr_off;
	double		x;
	double		a;
	double		rad;
	t_texture	tx;
	double		per_distance;
	double		distance_to_proj;
	double		proj_wall_height;
	int			wall_top_pixel;
	int			wall_bottom_pixel;
}	t_dwvars;

typedef struct s_data
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		**map;
	t_color		f;
	t_color		c;
	t_player	player;
	t_window	window;
	t_block		block;
	t_txtr		txtr;
	t_ray		*r;
	t_distance	distance;
	t_point		ply;
	t_point		stp;
	t_point		first_inter;
	t_point		a;
	t_point		t;
	int			i;
	int			j;
	int			map_width;
	int			map_height;
	double		map_x;
	double		map_y;
	t_point		centre_p;
	char		*tmp;
	double		rotation_speed;
	double		rays_degr;
	double		rays_inc;
	double		tile;
}	t_data;

char		*get_next_line(int fd);
void		my_mlx_pixel_put(t_window *data, int x, int y, int color);
void		init_window(t_data *data);
void		ft_block(t_data *data, double x, double y, int color);
int			check_player(char c);
int			draw_minimap(t_data *data);
void		move_player(t_data *data);
void		rotate_player(t_data *data);
void		draw_walls(t_data *data);
void		dda(t_data *data, t_segment segment, int color);
void		claculate_rays(t_data *data);
void		draw_rays(t_segment *seg, t_data *data);
int			get_map_width(t_data *data, int y);
int			draw(t_data *data);
int			run(t_data *data);
int			draw_minimap_frame(t_data *data);
int			draw_minimap2(t_data *data);
void		ft_block2(t_data *data, double x, double y, int color);
void		dda2(t_data *data, t_segment segment, int color);
void		draw_background(t_data *data);
int			get_color(char c);
void		get_texture(t_data *data);
double		h_distance(t_data *data, double beta);
double		v_distance(t_data *data, double beta);
void		claculate_rays(t_data *data);
void		best_distance(t_data *data, double beta);
double		normalize(double teta);
int			facing_right(double beta);
int			facing_down(double beta);
int			rgb_to_dec(t_color color);
void		move_map(t_data *data);
void		player_symbol(t_data *data, double x, double y, int color);
int			key_press(int key, t_data *data);
int			key_release(int key, t_data *data);
int			you_quit(void);
void		h_distance_calc(t_data *data, double beta);
void		h_distance_calc2(t_data *data, double beta);
void		v_distance_calc(t_data *data, double beta);
void		v_distance_calc2(t_data *data, double beta);
int			get_color(char c);
t_texture	which_texture(t_data *data, int i);
double		findmod(double a, double b);
double		normalize(double teta);
void		draw_rays(t_segment *seg, t_data *data);
void		fill_col(char	**sp, t_color *col, char *t);
void		error_n_free(char **sp, char	*t);
void		error_n_free2(char	**sp, char	*t);
int			check_valid_chars(char **s);
int			check_line_comp(char **s, int t, int i);
int			check_line(char **s);
void		check_map(char **s, t_data *data);
char		*get_ext(char *filename);
int			ft_check_exten(char *s);
int			ft_trima(char **a, int i);
int			ft_trima2(char *a);
char		**ft_trima3(char **a);
int			search_indx(char **args, char *indx);
int			tab_len(char **str);
void		check_space(char *s, t_data *data);
void		check_path(char *d, t_data *data);
int			txtr_error(char **args, char *key);
int			check_duplicates(char *str);
int			check_free(char	*str);
void		exit_n_free(t_data *data, int t);
void		get_player_data(t_data *data);
void		parse_data(t_data *data, char *temp);
int			check_assets(char **s, t_data *data);
char		*check_assets_loop(t_data *data, char **s, char	*str, char	**t);
void		parse_walls(t_data *data, char **args);
void		else_free(char	*tmp, char	**t);
//parsing

int			check_cama(char *s);
void		check_color_range(t_color col);
t_color		check_color(char **s, int i);
void		get_colors(t_data *data, char **s);
int			search_indx(char **args, char *indx);
void		check_map(char **s, t_data *data);
char		*intial_map_check(char *s, char **t, t_data *data);
int			tab_len(char **str);
int			check_valid(int c);
int			check_player(char c);
void		check_zero(char **s, int i, int j);
char		**ft_trima3(char **a);
int			get_map_width(t_data *data, int y);
void		exit_n_free(t_data *data, int t);
void		free_tab(char **tab);
void		check_map_err(char *s, t_data *data);
int			check_empty_lines(char *s, t_data *data, int len);
void		if_free(char	*str);
void		error_msg(t_data *data, int type);

#endif