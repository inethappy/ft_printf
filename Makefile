NAME	=	libftprintf.a
OUTPUT	=	ft_printf.out
CC		=	gcc
#CFLAGS	=	-Wall -Wextra -Werror
SOURCES	=	ft_printf.c flags.c printing.c print_numbers.c help_func_nb.c print_cs.c
OBJECTS	=	$(SOURCES:.c=.o)

all:	$(NAME)

$(NAME): 
	 $(CC) -c -g $(SOURCES) libft/*.c -I libft/libft.h
	# $(CC) -c ft_printf.h $(SOURCES)
	ar rc $(NAME) *.o
%.o: ./%.c
	gcc -o $@ -c $<
test:
	$(CC) -g -L. libft/libft.a $(SOURCES) main.c -o $(OUTPUT)
clean:
	rm -rf *.o 
	rm -rf libft/*.o
fclean: clean
	rm -rf $(NAME)
re: fclean all
