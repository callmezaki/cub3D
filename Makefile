NAME = cub3d
NAME_BONUS = cub3d_bonus
INCLUDE = Mandatory/cub3d.h
INCLUDE_B = Bonus/cub3d_bonus.h

SRC =	Mandatory/main.c          \
		Mandatory/get_next_line.c \
		Mandatory/window.c        \
		Mandatory/ft_block.c      \
		Mandatory/minimap.c	\
		Mandatory/dda.c	\
		Mandatory/draw.c \
		Mandatory/rays.c \
		Mandatory/draw_utils.c \
		Mandatory/colors_parse.c \
		Mandatory/check_map.c\
		Mandatory/check_map_utils.c\
		Mandatory/key_handling.c	\
		Mandatory/distance_calc.c	\
		Mandatory/draw_utils_2.c \
		Mandatory/colors_utils.c \
		Mandatory/check_utils.c \
		Mandatory/main_utils.c  \
		Mandatory/main_utils_2.c \
		Mandatory/main_utils_3.c \
		Mandatory/main_utils_4.c \

SRC_B =	Bonus/main_bonus.c          \
		Bonus/get_next_line_bonus.c \
		Bonus/window_bonus.c        \
		Bonus/ft_block_bonus.c      \
		Bonus/minimap_bonus.c	\
		Bonus/dda_bonus.c	\
		Bonus/draw_bonus.c \
		Bonus/rays_bonus.c \
		Bonus/draw_utils_bonus.c \
		Bonus/draw_utils2_bonus.c\
		Bonus/colors_parse_bonus.c \
		Bonus/check_map_bonus.c\
		Bonus/check_map_utils_bonus.c\
		Bonus/rays_utils_bonus.c \
		Bonus/doors_bonus.c \
		Bonus/sprites_bonus.c\
		Bonus/check_map2_bonus.c\
		Bonus/colors_parse_utils_bonus.c\
		Bonus/doors_utils_bonus.c\
		Bonus/walls_bonus.c\
		Bonus/sprites_utils_bonus.c\
		Bonus/keys_bonus.c\
		Bonus/main_utils_bonus.c\
		Bonus/main_utils_2_bonus.c\
		Bonus/main_utils_3_bonus.c\
		Bonus/main_utils_4_bonus.c\

CFLAGS = -Wall -Werror -Wextra -g -Ofast

OBJS = $(SRC:.c=.o)
OBJ_B = $(SRC_B:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft 
	@cc  $(CFLAGS) -I  $(INCLUDE) libft/libft.a -o $@ $^   -lmlx -framework OpenGL -framework AppKit 

bonus: $(NAME_BONUS)

$(NAME_BONUS):$(OBJ_B)
	@make -C libft 
	@cc  $(CFLAGS) -I $(INCLUDE_B) libft/libft.a -o $@ $^   -lmlx -framework OpenGL -framework AppKit 

clean:
	@rm -f $(OBJS) $(OBJ_B)
fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)
	@make fclean -C libft
re: fclean all

# -fsanitize=address