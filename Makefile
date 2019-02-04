NAME	=	libftprintf.a
OUTPUT	=	ft_printf.out
CC		=	gcc
#CFLAGS	=	-Wall -Wextra -Werror
SOURCES	=	ft_printf.c flags.c printing.c print_numbers.c
OBJECTS	=	$(SOURCES:.c=.o)

all:	$(NAME)

$(NAME): 
	 $(CC) -c -g $(SOURCES) libft/*.c -I libft/libft.h
	# $(CC) -c ft_printf.h $(SOURCES)
	ar rc $(NAME) *.o
%.o: ./%.c
	gcc -o $@ -c $<
test:
	$(CC) -g -L. libft/libft.a $(SOURCES) -o $(OUTPUT)
clean:
	rm -rf *.o 
	rm -rf libft/*.o
fclean: clean
	rm -rf $(NAME)
re: fclean all
