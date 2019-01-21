#ifndef FT_PRINTF_H
# define FT_PRINTF_H
#include <stdio.h>
#include <stdarg.h>

int ft_printf(const char *format, ...);
void	ft_putstr(char const *s);
void	ft_putnbr(int n);
void	ft_putchar(char c);

#endif