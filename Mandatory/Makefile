NAME = cub3d
INCLUDE = cub3d.h 

SRC =	cub3d.c         \
		main.c          \
		get_next_line.c \
		window.c        \
		ft_block.c      \
		minimap.c	\
		dda.c	\
		draw.c \
		rays.c \
		draw_utils.c \
		colors_parse.c \
		check_map.c\
		check_map_utils.c\
		key_handling.c	\
		distance_calc.c	\
		draw_utils_2.c \
		colors_utils.c \
		check_utils.c \
		main_utils.c  \
		main_utils_2.c \
		main_utils_3.c \
		main_utils_4.c \


CFLAGS = -Wall -Werror -Wextra -g -Ofast

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft 
	@gcc  $(CFLAGS) -I  $(INCLUDE) libft/libft.a -o $@ $^   -lmlx -framework OpenGL -framework AppKit 


clean:
	@rm -f $(OBJS)
fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft
re: fclean all

# -fsanitize=address