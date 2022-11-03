NAME = cub3d
INCLUDE = cub3d.h 

SRC =	cub3d.c         \
		main.c          \
		get_next_line.c \
		window.c        \
		ft_block.c      \
		minimap.c	\
		DDA.c	\
		draw.c \
		rays.c \
		draw_utils.c \
		colors_parse.c \
		check_map.c\
		check_map_utils.c\
		rays_utils.c \
		doors.c \
		sprites.c\

CFLAGS = -Wall -Werror -Wextra -g -Ofast

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRC)
	@make -C libft 
	@gcc  $(CFLAGS) -I  $(INCLUDE) libft/libft.a -o $@ $^   -lmlx -framework OpenGL -framework AppKit -g


man:
	@cat README.md
clean:
	@rm -f $(OBJS)
fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft
re: fclean all

# -fsanitize=address