C := gcc
CFLAGS := -Wall -Werror -Wextra
CFILES := cub3d.c \
		main.c \
		get_next_line.c \
        libft/ft_strlen.c     \
        libft/ft_strchr.c     \
        libft/ft_strrchr.c    \
        libft/ft_strncmp.c    \
        libft/ft_strlcpy.c    \
        libft/ft_strnstr.c    \
        libft/ft_atoi.c       \
        libft/ft_strdup.c     \
        libft/ft_substr.c     \
        libft/ft_strjoin.c    \
        libft/ft_strtrim.c    \
        libft/ft_split.c      \
        libft/ft_itoa.c       \
 
OFILES := $(CFILES:.c=.o)

INC := cub3d.h
LIB = /libft

NAME := cub3d
	
	
$(NAME) : $(OFILES) $(INC)  
	$(CC) $(CFLAGS) -I $(LIB) $(CFILES) -o $(NAME)

	

all : $(NAME)

clean :
	@rm -rf $(OFILES)
	@rm -rf $(BOFILES)
fclean : clean
	@make fclean -C libft
	@rm -rf $(NAME)
	@rm -rf $(BNAME)

re : fclean all
reb : fclean bonus