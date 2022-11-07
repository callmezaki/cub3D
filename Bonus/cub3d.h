/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:54:52 by zait-sli          #+#    #+#             */
/*   Updated: 2022/11/07 00:46:46 by sgmira           ###   ########.fr       */
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
# define STEP 1
# define FOV 60
# define RAYS W_WIDTH

# define KEY_W 13 
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53
# define KEY_SPACE 49
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

typedef struct s_door
{
	int				h_or_v;
	int				h_or_v_door;
	int				hit_door;
	double			x_door;
	double			y_door;
	double			dis_door;
	struct s_door	*next;
}	t_door;

typedef struct s_dis
{
	t_point	a;
	t_point	first_inter;
	t_point	t;
	t_point	stp;
	double	dis;
	t_point	ply;
	double	beta;
	int		h_or_v;
}t_dis;

typedef struct s_ray
{
	double	x;
	double	y;
	double	distance;
	double	alpha;
	int		hit_door;
	int		h_is_door;
	int		v_is_door;
	double	v_door;
	double	h_door;
	int		h_or_v;
	t_door	*door;
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

typedef struct s_sprite
{
	double		x;
	double		y;
	double		dis;
	t_texture	tx;
	double		angle;
	int			vis;
	int			drown;
}	t_sprite;

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
	int			is_m_pressed;
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

typedef struct s_dwvars
{
	int			i;
	int			j;
	t_point		txtr_off;
	double		x;
	int			h;
	double		a;
	double		k;
	double		rad;
	t_texture	tx;
	double		per_distance;
	double		distance_to_proj;
	double		proj_wall_height;
	int			wall_top_pixel;
	int			wall_bottom_pixel;
}	t_dwvars;

typedef struct s_dwsprite
{
	int			i;
	int			j;
	t_point		t;
	double		rad;
	double		dis_to_proj;
	double		sp_height;
	double		sp_width;
	double		sp_topy;
	double		sp_bottomy;
	double		sp_sc_posx;
	double		sp_leftx;
	double		sp_rightx;
	t_texture	tx;
	t_point		txtr_off;
	double		distance_from_top;
	double		tp;
	int			h;
}	t_dwsprite;

typedef struct s_txtr
{
	t_texture	north;
	t_texture	south;
	t_texture	east;
	t_texture	west;
	t_texture	door;
	t_texture	d_f0;
	t_texture	d_f1;
	t_texture	d_f2;
	t_texture	d_f3;
	t_texture	d_f4;
	t_texture	d_f5;
	t_texture	d_f6;
	t_texture	s0;
	t_texture	s1;
	t_texture	s2;
	t_texture	s3;
	t_texture	sp;
}	t_txtr;

typedef struct s_data
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*doo;
	char		**map;
	t_color		f;
	t_color		c;
	t_player	player;
	t_window	window;
	t_block		block;
	t_door		door;
	t_txtr		txtr;
	t_ray		*r;
	t_distance	distance;
	int			i;
	int			j;
	int			map_width;
	int			map_height;
	double		map_x;
	double		map_y;
	int			open_door;
	int			an;
	t_point		centre_p;
	t_sprite	*sprites;
	int			sp;
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
double		h_distance(t_data *data, double beta, t_ray *ray);
double		v_distance(t_data *data, double beta, t_ray *ray);
void		claculate_rays(t_data *data);
void		best_distance(t_data *data, double beta, t_ray *ray);
double		normalize(double teta);
int			facing_right(double beta);
int			facing_down(double beta);
int			rgb_to_dec(t_color color);
void		move_map(t_data *data);
void		player_symbol(t_data *data, double x, double y, int color);
void		draw_sprite(t_data *data, int x);
int			mouse_press(int key, int x, int y, t_data *data);
int			mouse_release(int key, int x, int y, t_data *data);
int			mouse_move(int x, int y, t_data *data);
int			key_release(int key, t_data *data);
int			key_press(int key, t_data *data);
int			you_quit(void);
void		draw_doors(t_data *data);
t_door		*ft_new(t_door d);
void		ft_add_front(t_door **lst, t_door *new);
t_texture	which_door_texture(t_data *data, t_door *door);
void		cast_door_ray(t_door *door, t_data *data, int i);
void		free_list(t_door *door);
int			return_firstx(t_data *data, t_sprite sp);
void		draw_doors(t_data *data);

void		sort_sprites(t_data *data);
t_texture	which_sprite_texture(t_data *data);
void		get_sprite_data(t_data *data);
int			check_dis(t_data *data, int x, int i);
void		draw_sprite_rays(t_dwsprite *dsp, t_data *data, int x);
void		draw_sprite(t_data *data, int x);
void		draw_rest_sprites(t_data *data);
void		check_map_comp(int check, t_data *data);
void		check_map(char **s, t_data *data);
int			check_check(char **s, t_data *data);
int			check_doors(char **s, int i, int j);
int			check_cama(char *s);
void		check_color_range(t_color col);
void		check_compl(char **ss, t_color *col, char	**sp, char	*t);
int			check_dis(t_data *data, int x, int i);
void		sort_sprites(t_data *data);
t_texture	which_sprite_texture(t_data *data);
//parsing

void		key_press_cond(int key, t_data *data);
int			key_press(int key, t_data *data);
int			key_release(int key, t_data *data);
int			mouse_press(int key, int x, int y, t_data *data);
int			mouse_release(int key, int x, int y, t_data *data);

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
void		check_zero(char **s, int i, int j, t_data *data);
char		**ft_trima3(char **a);
int			get_map_width(t_data *data, int y);
void		exit_n_free(t_data *data, int t);
void		free_tab(char **tab);
char		*get_ext(char *filename);
int			ft_check_exten(char *s);
int			ft_trima(char **a, int i);
int			ft_trima2(char *a);
void		check_space(char *s, t_data *data);
void		check_path(char *d, t_data *data);
int			txtr_error(char **args, char *key);
void		parse_walls(t_data *data, char **args);
char		*check_assets_loop(t_data *data, char **s, char	*str, char	**t);
int			check_assets(char **s, t_data *data);
int			check_duplicates(char *str);
void		get_player_data(t_data *data);
char		*get_data_loop(t_data *data, char	*str, int fd, char	*temp);
void		get_data(int fd, t_data *data);
void		parse_walls_2(t_data *data, char **args);
void		get_player_data_calc(t_data *data, int i, int j);
void		parse_data(t_data *data, char *temp);
void		error_msg(t_data *data, int type);

#endif