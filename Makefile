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

CFLAGS = -Wall -Werror -Wextra -g

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