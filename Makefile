NAME	=	libftprintf.a
OUTPUT	=	ft_printf.out
CC		=	gcc
#CFLAGS	=	-Wall -Wextra -Werror
SOURCES	=	ft_printf.c flags.c
			#flags.c
OBJECTS	=	$(SOURCES:.c=.o)

all:	$(NAME)
$(NAME):
	$(CC) -c -g $(SOURCES) -I libft/libft.h
	ar rc $(NAME) $(OBJECTS)
test:
	$(CC) -L. libft/libft.a $(SOURCES) -o $(OUTPUT)
clean:
	rm -rf $(OBJECTS) libft/*.o
fclean: clean
	rm -rf $(NAME)
re: fclean all
